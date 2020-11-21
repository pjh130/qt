#ifndef QHTTPSERVER_H
#define QHTTPSERVER_H

#include <QThread>
#include <QHttpRequest>
#include "qasyntcpserver.h"

class QHttpServer : public QAsynTcpServer

{

Q_OBJECT

public:

QHttpServer(QObject *parent = 0,int numConnections=1000);

virtual ~QHttpServer();

private Q_SLOTS:

void handleRequest(QHttpRequest *request, QHttpResponse *response);

protected slots:

void sockDisConnectSlot(int handle,const QString & ip, quint16 prot, QThread *th);//断开连接的用户信息

protected:

void incomingConnection(qintptr socketDescriptor);//覆盖已获取多线程

};

#endif // QHTTPSERVER_H
