#include "tcpserver.h"
#include <QDebug>
TcpServer::TcpServer(QObject *parent):
    QTcpServer(parent)
{

}

TcpServer::~TcpServer()
{

}

void TcpServer::incomingConnection(qintptr handle)
{
    TcpThread *thread = new TcpThread(handle, this);

    qDebug()<<"New connection: "<<handle<<endl;
    connect(thread, SIGNAL(finished()),thread, SLOT(deleteLater()));
    connect(thread, SIGNAL(started()), this, SLOT(slotTest()));
    connect(thread,SIGNAL(sigBytesArrived(qint64,qint32,int)),this,SIGNAL(sigBytesArrived(qint64,qint32,int)));

    thread->start();
}

void TcpServer::slotTest()
{
    qDebug()<<"slotTest";
}

