#include "tcpsocketclient.h"

TcpSocketClient::TcpSocketClient()
{
    m_sockect = NULL;
}

TcpSocketClient::~TcpSocketClient()
{
    closeSockect();
}

void TcpSocketClient::closeSockect()
{
    if(m_sockect)
    {
        m_sockect->close();
        m_sockect->deleteLater();
        m_sockect = NULL;
    }
}

void TcpSocketClient::slotStartSocket(const QString &strIp, const quint16 port)
{
    qDebug()<<"TcpSocketClient::slotStartSocket";
    m_sockect = new QTcpSocket;
    m_strIp = strIp;
    m_port = port;
    connect(m_sockect,&QTcpSocket::readyRead,this,&TcpSocketClient::slotReadData);
    dis = connect(m_sockect,&QTcpSocket::disconnected,
        [&](){
            qDebug() << "disconnect" ;
            closeSockect();
            emit sockDisConnect(m_socketID, m_strIp, m_port, QThread::currentThread());//发送断开连接的用户信息
        });
    m_sockect->connectToHost(m_strIp, port);
    QEventLoop loop;
    connect(m_sockect, &QTcpSocket::stateChanged, &loop, &QEventLoop::quit);
    //加个超时
//    QTimer::singleShot(30, &loop, SLOT(quit()));
    loop.exec();
//    return;
    if(m_sockect->state() == QTcpSocket::ConnectedState)
    {
        emit connectClient(m_socketID, m_strIp, m_port);
        qDebug() << "new connect-->"<<m_strIp<<":"<<m_port ;
    } else {
        qDebug() << "connect failed-->"<<m_strIp<<":"<<m_port<<"  "<<m_sockect->errorString();
        emit connectClient(-1, m_strIp, m_port);
        closeSockect();
    }
}

void TcpSocketClient::slotSentData(const qintptr socketID, const QString &strKey, const QByteArray &data)
{
    qDebug()<<"TcpSocketClient::slotSentData currentThreadId: "<<QThread::currentThreadId();
    if(m_sockect == NULL)
    {
        return;
    }

    if(socketID == m_socketID)
    {
        //只发送匹配自己的数据
        qint64 send =  m_sockect->write(data);
        if (send == data.length())
        {
            //成功
            emit sendDataRet(m_socketID, strKey, true, "");
        } else {
            //失败
            emit sendDataRet(m_socketID, strKey, false, m_sockect->errorString());
        }
    } else if(-1 == socketID ){
        //默认是数据群发
        qint64 send = m_sockect->write(data);
        if (send == data.length())
        {
            //成功
            emit sendDataRet(m_socketID, strKey, true, "");
        } else {
            //失败
            emit sendDataRet(m_socketID, strKey, false, m_sockect->errorString());
        }
    } else {
        //不做任何处理
    }
}

void TcpSocketClient::disConTcp(const qintptr socketID)
{
    if(m_sockect == NULL)
    {
        return;
    }

    if (socketID == m_socketID)
    {
        m_sockect->disconnectFromHost();
    }
    else if (socketID == -1) //-1为全部断开
    {
        disconnect(dis); //先断开连接的信号槽，防止二次析构
        m_sockect->disconnectFromHost();
        m_sockect->deleteLater();
        m_sockect = NULL;
    }
}

void TcpSocketClient::slotReadData()
{
    qDebug()<<"TcpSocketClient::slotReadData currentThreadId: "<<QThread::currentThreadId();

    if(m_sockect == NULL)
    {
        return;
    }

    QByteArray data  = m_sockect->readAll();

    //收到的数据不做处理转发出去
    emit receiveData(m_socketID, data);
}


