#include "tcpserver.h"
#include "threadhandle.h"

TcpServer::TcpServer(QObject *parent,int numConnections) :
    QTcpServer(parent)
{
    //注册自定义的信号槽参数
    qRegisterMetaType<qintptr>("qintptr");

     tcpClient = new  QHash<int,TcpSocket *>;
     setMaxPendingConnections(numConnections);
}

TcpServer::~TcpServer()
{
    emit this->sentDisConnect(-1);
    delete tcpClient;
}

void TcpServer::setMaxPendingConnections(int numConnections)
{
    this->QTcpServer::setMaxPendingConnections(numConnections);//调用Qtcpsocket函数，设置最大连接数，主要是使maxPendingConnections()依然有效
    this->maxConnections = numConnections;
}

void TcpServer::incomingConnection(qintptr socketDescriptor) //多线程必须在此函数里捕获新连接
{
    if (tcpClient->size() > maxPendingConnections())//继承重写此函数后，QTcpServer默认的判断最大连接数失效，自己实现
    {
        QTcpSocket tcp;
        tcp.setSocketDescriptor(socketDescriptor);
        tcp.disconnectFromHost();
        return;
    }
    auto th = ThreadHandle::getClass().getThread();
    auto tcpTemp = new TcpSocket(socketDescriptor);
    QString ip =  tcpTemp->peerAddress().toString();
    qint16 port = tcpTemp->peerPort();

    connect(tcpTemp,&TcpSocket::sockDisConnect,this,&TcpServer::sockDisConnectSlot);//NOTE:断开连接的处理，从列表移除，并释放断开的Tcpsocket，此槽必须实现，线程管理计数也是考的他
    connect(this,&TcpServer::sentDisConnect,tcpTemp,&TcpSocket::disConTcp);//断开信号
    connect(this,&TcpServer::sentData,tcpTemp,&TcpSocket::slotSentData);//发送数据
    connect(tcpTemp,&TcpSocket::sendDataRet, this,&TcpServer::slotSendDataRet);//发送数据的结果
    connect(tcpTemp,&TcpSocket::receiveData, this,&TcpServer::slotReceiveData);//接收客户端发送来的数据

    tcpTemp->moveToThread(th);//把tcp类移动到新的线程，从线程管理类中获取
    tcpClient->insert(socketDescriptor,tcpTemp);//插入到连接信息中

    emit connectClient(socketDescriptor,ip,port);

    //测试发送一条欢迎消息
    emit sentData(socketDescriptor, QUuid::createUuid().toString(), "Hello");
}

void TcpServer::sockDisConnectSlot(const qintptr socketID , const QString &strIp,
                                   const quint16 port, QThread *thread)
{
    tcpClient->remove(socketID);//连接管理中移除断开连接的socket
    ThreadHandle::getClass().removeThread(thread); //告诉线程管理类那个线程里的连接断开了
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
    tcpClient->clear();
}
