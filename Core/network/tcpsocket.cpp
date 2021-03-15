#include "tcpsocket.h"
#include <QtConcurrent/QtConcurrent>
#include <QHostAddress>
#include <QDebug>

TcpSocket::TcpSocket(qintptr socketDescriptor, QObject *parent) : //构造函数在主线程执行，lambda在子线程
    QTcpSocket(parent),m_socketID(socketDescriptor)
{
    qDebug()<<"TcpSocket::TcpSocket: "<<QThread::currentThreadId();
    this->setSocketDescriptor(socketDescriptor);
    m_strIp = this->peerAddress().toString();
    m_port = this->peerPort();
    connect(this,&TcpSocket::readyRead,this,&TcpSocket::slotReadData);
    dis = connect(this,&TcpSocket::disconnected,
        [&](){
            qDebug() << "disconnect" ;
            emit sockDisConnect(m_socketID, m_strIp, m_port, QThread::currentThread());//发送断开连接的用户信息
            this->deleteLater();
        });

    emit connectClient(m_socketID, m_strIp, m_port);
    qDebug() << "new connect-->"<<m_strIp<<":"<<m_port ;
}

TcpSocket::~TcpSocket()
{
}


void TcpSocket::slotSentData(SEND_DATA_ST st)
{
    qDebug()<<"TcpSocket::slotSentData: "<<QThread::currentThreadId();
    if(st.socketID == m_socketID || -1 == st.socketID)
    {
        //只发送匹配自己的数据
        qint64 send = write(st.byData);
        if (send == st.byData.length())
        {
            //成功
            emit sendDataRet(m_socketID, st.strKey, true, "");
        } else {
            //失败
            emit sendDataRet(m_socketID, st.strKey, false, errorString());
        }
    } else {
        //不做任何处理
    }
}

void TcpSocket::disConTcp(const qintptr socketID)
{
    if (socketID == m_socketID)
    {
        this->disconnectFromHost();
    }
    else if (socketID == -1) //-1为全部断开
    {
        disconnect(dis); //先断开连接的信号槽，防止二次析构
        this->disconnectFromHost();
        this->deleteLater();
    }
}

void TcpSocket::slotReadData()
{
    qDebug()<<"TcpSocket::slotReadData: "<<QThread::currentThreadId();
    QByteArray data  = this->readAll();

    //收到的数据不做处理转发出去
    emit receiveData(m_socketID, data);
}
