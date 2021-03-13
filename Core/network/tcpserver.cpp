#include "tcpserver.h"
#include "threadhandle.h"

TcpServer::TcpServer(QObject *parent,int numConnections) :
    QTcpServer(parent)
{
    m_bUse_1_or_2 = false;  //1-true, 2-false
    //注册自定义的信号槽参数
    qRegisterMetaType<qintptr>("qintptr");

    setMaxPendingConnections(numConnections);
}

TcpServer::~TcpServer()
{
    emit this->sentDisConnect(-1);
}

void TcpServer::setMaxPendingConnections(int numConnections)
{
    this->QTcpServer::setMaxPendingConnections(numConnections);//调用Qtcpsocket函数，设置最大连接数，主要是使maxPendingConnections()依然有效
    this->maxConnections = numConnections;
}

void TcpServer::incomingConnection(qintptr socketDescriptor) //多线程必须在此函数里捕获新连接
{
    qDebug()<<"TcpServer::incomingConnection: "<<QThread::currentThreadId();
    if (m_bUse_1_or_2)
    {
        if (tcpClient1.size() > maxPendingConnections())//继承重写此函数后，QTcpServer默认的判断最大连接数失效，自己实现
        {
            QTcpSocket tcp;
            tcp.setSocketDescriptor(socketDescriptor);
            tcp.disconnectFromHost();
            return;
        }

        getSockect1(socketDescriptor);
    } else {
        if (tcpClient2.size() > maxPendingConnections())//继承重写此函数后，QTcpServer默认的判断最大连接数失效，自己实现
        {
            QTcpSocket tcp;
            tcp.setSocketDescriptor(socketDescriptor);
            tcp.disconnectFromHost();
            return;
        }

        getSockect2(socketDescriptor);
    }

    //测试发送一条欢迎消息
    emit sentData(socketDescriptor, QUuid::createUuid().toString(), "Hello");
}

void TcpServer::getSockect1(qintptr socketDescriptor)
{
    auto th = ThreadHandle::getClass().getThread();
    auto tcpTemp = new TcpSocket(socketDescriptor);

    connect(tcpTemp,&TcpSocket::sockDisConnect,this,&TcpServer::sockDisConnectSlot);//NOTE:断开连接的处理，从列表移除，并释放断开的Tcpsocket，此槽必须实现，线程管理计数也是考的他
    connect(this,&TcpServer::sentDisConnect,tcpTemp,&TcpSocket::disConTcp);//断开信号
    connect(this,&TcpServer::sentData,tcpTemp,&TcpSocket::slotSentData);//发送数据
    connect(tcpTemp,&TcpSocket::sendDataRet, this,&TcpServer::slotSendDataRet);//发送数据的结果
    connect(tcpTemp,&TcpSocket::receiveData, this,&TcpServer::slotReceiveData);//接收客户端发送来的数据
    connect(tcpTemp,&TcpSocket::connectClient, this,&TcpServer::connectClient); //通知连接

    tcpTemp->moveToThread(th);//把tcp类移动到新的线程，从线程管理类中获取
    tcpClient1.insert(socketDescriptor,tcpTemp);//插入到连接信息中
}
void TcpServer::getSockect2(qintptr socketDescriptor)
{
    auto tcpTemp = new TcpSocketThread;

    connect(this,&TcpServer::startSocket,tcpTemp,&TcpSocketThread::slotStartSocket);//开始工作
    connect(this,&TcpServer::sentDisConnect,tcpTemp,&TcpSocketThread::disConTcp);//断开信号
    connect(this,&TcpServer::sentData,tcpTemp,&TcpSocketThread::slotSentData);//发送数据
    connect(tcpTemp,&TcpSocketThread::sockDisConnect,this,&TcpServer::sockDisConnectSlot);//NOTE:断开连接的处理，从列表移除，并释放断开的Tcpsocket，此槽必须实现，线程管理计数也是考的他
    connect(tcpTemp,&TcpSocketThread::sendDataRet, this,&TcpServer::slotSendDataRet);//发送数据的结果
    connect(tcpTemp,&TcpSocketThread::receiveData, this,&TcpServer::slotReceiveData);//接收客户端发送来的数据
    connect(tcpTemp,&TcpSocketThread::connectClient, this,&TcpServer::connectClient); //通知连接

    tcpClient2.insert(socketDescriptor,tcpTemp);//插入到连接信息中
//    tcpTemp->start();

    emit startSocket(socketDescriptor);
}

void TcpServer::sockDisConnectSlot(const qintptr socketID , const QString &strIp,
                                   const quint16 port, QThread *thread)
{
    qDebug()<<"TcpServer::sockDisConnectSlot: "<<socketID;
    if(m_bUse_1_or_2)
    {
        if(tcpClient1.contains(socketID))
        {
            TcpSocket *socket = tcpClient1.value(socketID);
            tcpClient1.remove(socketID);//连接管理中移除断开连接的socket
            socket->deleteLater();
        }

        ThreadHandle::getClass().removeThread(thread); //告诉线程管理类那个线程里的连接断开了
    } else {
        if(tcpClient2.contains(socketID))
        {
            TcpSocketThread *socket = tcpClient2.value(socketID);
            tcpClient1.remove(socketID);//连接管理中移除断开连接的socket
            socket->deleteLater();
        }
    }
    emit sockDisConnect(socketID, strIp, port);
}

void TcpServer::slotReceiveData(const qintptr socketID, const QByteArray data)
{
    qDebug()<<"slotReceiveData socketID: "<<socketID<<" "<<data;
}

void TcpServer::slotSendDataRet(const qintptr socketID, const QString &strKey,
                                const bool &bOk, const QString &strError)
{
    //    qDebug()<<"slotSendDataRet: "<<QThread::currentThreadId();
    qDebug()<<"slotSendDataRet socketID: "<<socketID<<" "<<bOk<<" "<<strKey;
    strError.isEmpty();
}

void TcpServer::clear()
{
    emit this->sentDisConnect(-1);
    ThreadHandle::getClass().clear();
    tcpClient1.clear();
    tcpClient2.clear();
}
