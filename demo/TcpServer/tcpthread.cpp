#include "tcpthread.h"



TcpThread::TcpThread(qintptr handle, QObject *parent):
    QThread(parent),m_handle(handle)
{
    m_pTcp = NULL;
}

TcpThread::~TcpThread()
{

}

void TcpThread::run()
{
    m_pTcp = new QTcpSocket();

    if (m_pTcp->setSocketDescriptor(m_handle))
    {
        qDebug()<<"setSocketDescriptor err: "<<m_pTcp->errorString();
//        return;
    }
    //注意this对象是在外边new的，所以和 m_pTcp 是不在同一个线程内。 DirectConnection是表示接收者在信号发送的线程执行
    connect(m_pTcp, SIGNAL(readyRead()), this, SLOT(readData()), Qt::DirectConnection);
    qRegisterMetaType<QAbstractSocket::SocketError>("QAbstractSocket::SocketError");
    connect(m_pTcp, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(errorString(QAbstractSocket::SocketError)), Qt::DirectConnection);

    exec();
}

void TcpThread::readData()
{
    if (m_pTcp != NULL)
    {
        qDebug()<<m_pTcp->readAll()<<endl;
        m_pTcp->write("OK");
    } else {
         qDebug()<<"m_pTcp is NULL"<<endl;
    }
}

void TcpThread::errorString(QAbstractSocket::SocketError)
{
    return;
//    emit sigError(socketError);

    if (m_pTcp)
    {
        qDebug()<<"SocketError: "<<m_pTcp->errorString()<<endl;
        m_pTcp->close();
        m_pTcp->deleteLater();
        m_pTcp = NULL;
    }
//    this->exit();
}

