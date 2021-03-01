#include "udpex.h"

#include <QByteArray>

UdpEx::UdpEx()
    : QUdpSocket()
{
    m_recvObject = NULL;
}

UdpEx::~UdpEx()
{
    close();
}

int UdpEx::start(int Port)
{
    close();
    if ( bind(Port, QUdpSocket::ShareAddress) )
    {
        connect(this, SIGNAL(readyRead()), this, SLOT(udpRecv()));
    }
    return isValid() ? this->localPort() : 0;
}

void UdpEx::udpRecv()
{
    while( hasPendingDatagrams() )
    {
        QByteArray datagram;
        datagram.resize(pendingDatagramSize());
        QHostAddress client;
        readDatagram(datagram.data(), datagram.size(), &client);

        if ( m_recvObject != NULL
          && m_recvObject->metaObject()->invokeMethod(m_recvObject, m_recvMethod.data(),
                                                      Q_ARG(UdpEx*, this),
                                                      Q_ARG(QHostAddress, client),
                                                      Q_ARG(QByteArray, datagram)) )
        {
        }else
        {
            Q_EMIT recvMessage(client, datagram);
        }
    }
}

bool UdpEx::sendMessage(QHostAddress host, int port, QByteArray S)
{
    qint64 len = S.size();
    return writeDatagram(S.constData(), S.size(), host, port) == len;
}

void UdpEx::sendBroadcast(int port, QByteArray S)
{
    writeDatagram(S, QHostAddress::Broadcast, port);
}


