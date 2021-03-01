#include "tcpsocket.h"
#include <QtConcurrent/QtConcurrent>
#include <QHostAddress>
#include <QDebug>

TcpSocket::TcpSocket(qintptr socketDescriptor, QObject *parent) : //构造函数在主线程执行，lambda在子线程
    QTcpSocket(parent),m_socketID(socketDescriptor)
{
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

    qDebug() << "new connect-->"<<m_strIp<<":"<<m_port ;
}

TcpSocket::~TcpSocket()
{
}


void TcpSocket::slotSentData(const qintptr socketID, const QString &strKey, const QByteArray &data)
{
    if(socketID == m_socketID)
    {
        qint64 send = write(data);
        if (send == data.length())
        {
            //成功
            emit sendDataRet(m_socketID, strKey, true, "");
        } else {
            //失败
            emit sendDataRet(m_socketID, strKey, false, errorString());
        }
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
    QByteArray data  = this->readAll();

    //收到的数据不做处理转发出去
    emit receiveData(m_socketID, data);
}
