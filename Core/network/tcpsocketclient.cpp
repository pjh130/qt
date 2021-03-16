#include "tcpsocketclient.h"

TcpSocketClient::TcpSocketClient(const QString &strIp, const quint16 port, QObject *parent):
    TcpSocketThread(-1, parent)
{
    m_timer = NULL;
    m_sockect = NULL;
    m_strIpSer = strIp;
    m_portSer = port;
    m_socketID = -1;
}

TcpSocketClient::~TcpSocketClient()
{

}

void TcpSocketClient::run()
{
    m_timer = new QTimer;
    connect(m_timer, SIGNAL(timeout()), this, SLOT(slotWork()), Qt::DirectConnection);
    m_timer->start(100);

    m_sockect = new QTcpSocket;

    connect(m_sockect,&QTcpSocket::readyRead,this,&TcpSocketThread::slotReadData, Qt::DirectConnection);
    dis = connect(m_sockect, &QTcpSocket::disconnected, this, &TcpSocketThread::slotDisconnect, Qt::DirectConnection);
    m_sockect->connectToHost(m_strIpSer, m_portSer);
    QEventLoop loop;
    connect(m_sockect, &QTcpSocket::stateChanged, &loop, &QEventLoop::quit);
    loop.exec();
    if(m_sockect->state() == QTcpSocket::ConnectedState)
    {
        m_strIp = m_sockect->peerAddress().toString();
        m_port = m_sockect->peerPort();
        m_socketID = m_sockect->socketDescriptor();
        emit connectClient(m_socketID, m_strIp, m_port);
        qDebug() << "new connect-->"<<m_strIp<<":"<<m_port;
    } else {
        qDebug() << "connect failed-->"<<m_strIp<<":"<<m_port<<"  "<<m_sockect->errorString();
        emit sockDisConnect(m_socketID, m_strIpSer, m_portSer, QThread::currentThread());
        stopTimer();
        closeSockect();
        return;
    }

    exec();
}
