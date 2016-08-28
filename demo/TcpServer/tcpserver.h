#ifndef TCPSERVER_H
#define TCPSERVER_H

#include <QTcpServer>
#include "tcpthread.h"

class TcpServer : public QTcpServer
{
public:
     explicit TcpServer(QObject *parent = 0);
    ~TcpServer();

signals:
    void sigBytesArrived(qint64,qint32,int);

public slots:
    void slotTest();

protected:
    void incomingConnection(qintptr handle);
};

#endif // TCPSERVER_H
