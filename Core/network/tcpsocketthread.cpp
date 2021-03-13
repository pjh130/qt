#include "tcpsocketthread.h"

TcpSocketThread::TcpSocketThread()
{
    m_sockect = NULL;
}

TcpSocketThread::~TcpSocketThread()
{
    closeSockect();
}

void TcpSocketThread::closeSockect()
{
    if(m_sockect)
    {
        m_sockect->close();
        m_sockect->deleteLater();
        m_sockect = NULL;
    }
}

void TcpSocketThread::slotStartSocket(qintptr socketDescriptor)
{
    m_socketID = socketDescriptor;
    m_sockect = new QTcpSocket;
    m_sockect->setSocketDescriptor(socketDescriptor);
    m_strIp = m_sockect->peerAddress().toString();
    m_port = m_sockect->peerPort();
    connect(m_sockect,&QTcpSocket::readyRead,this,&TcpSocketThread::slotReadData);
    dis = connect(m_sockect,&QTcpSocket::disconnected,
        [&](){
            qDebug() << "disconnect" ;
            closeSockect();
            emit sockDisConnect(m_socketID, m_strIp, m_port, QThread::currentThread());//发送断开连接的用户信息
        });

    emit connectClient(m_socketID, m_strIp, m_port);
    qDebug() << "new connect-->"<<m_strIp<<":"<<m_port ;
}

void TcpSocketThread::slotSentData(const qintptr socketID, const QString &strKey, const QByteArray &data)
{
    qDebug()<<"TcpSocketThread::slotSentData currentThreadId: "<<QThread::currentThreadId();
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

void TcpSocketThread::disConTcp(const qintptr socketID)
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

void TcpSocketThread::slotReadData()
{
    if(m_sockect == NULL)
    {
        return;
    }

    qDebug()<<"TcpSocketThread::slotReadData currentThreadId: "<<QThread::currentThreadId();
    QByteArray data  = m_sockect->readAll();

    //收到的数据不做处理转发出去
    emit receiveData(m_socketID, data);
}

