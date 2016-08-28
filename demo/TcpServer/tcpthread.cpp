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
    connect(m_pTcp, SIGNAL(readyRead()), this, SLOT(readData()), Qt::BlockingQueuedConnection);

    connect(m_pTcp, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(errorString(QAbstractSocket::SocketError)), Qt::BlockingQueuedConnection);

    exec();
}

void TcpThread::readData()
{
    qDebug()<<m_pTcp->readAll()<<endl;
    m_pTcp->write("OK");
}

void TcpThread::errorString(QAbstractSocket::SocketError)
{
//    emit sigError(socketError);

    if (m_pTcp)
    {
        qDebug()<<"SocketError: "<<m_pTcp->errorString()<<endl;
        m_pTcp->close();
        m_pTcp->deleteLater();
    }
    this->exit();
}

