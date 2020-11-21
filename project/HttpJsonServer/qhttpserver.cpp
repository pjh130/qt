#include "qhttpserver.h"

QHttpServer::QHttpServer()
{

}

void QHttpServer::incomingConnection(qintptr socketDescriptor)
{
    qDebug() << "QHttpServer:incomingConnection,ThreadId:"<<QThread::currentThreadId()  ;

    //继承重写此函数后，QQAsynTcpServer默认的判断最大连接数失效，自己实现
    if (m_ClientList->size() > maxPendingConnections())
    {
        QTcpSocket tcp;
        tcp.setSocketDescriptor(socketDescriptor);
        tcp.disconnectFromHost();
        qDebug() << "tcpClient->size() > maxPendingConnections(),disconnectFromHost";
        return;
    }
    auto th = ThreadHandle::getClass().getThread();
    QAsynHttpSocket* tcpTemp = new QAsynHttpSocket(socketDescriptor);
    QString ip =  tcpTemp->peerAddress().toString();
    qint16 port = tcpTemp->peerPort();

    //NOTE:断开连接的处理，从列表移除，并释放断开的Tcpsocket，线程管理计数减1,此槽必须实现
    connect(tcpTemp,SIGNAL(sockDisConnect(const int ,const QString &,const quint16, QThread *)),
            this,SLOT(sockDisConnectSlot(const int ,const QString &,const quint16, QThread *)));

    //必须在QAsynHttpSocket的线程中执行
    connect(tcpTemp, SIGNAL(newRequest(QHttpRequest *, QHttpResponse *)), this,
            SLOT(handleRequest(QHttpRequest *, QHttpResponse *)), Qt::DirectConnection);

    tcpTemp->moveToThread(th);//把tcp类移动到新的线程，从线程管理类中获取
    m_ClientList->insert(socketDescriptor,tcpTemp);//插入到连接信息中

    qDebug() << "QHttpServer m_ClientList add:"<<socketDescriptor  ;
}

void QHttpServer::handleRequest(QHttpRequest *req, QHttpResponse *resp)

{

    qDebug() << "QHttpServer:handleRequest,ThreadId:"<<QThread::currentThreadId()  ;

    qDebug() <<"path:"<< req->path();

    QJsonDocument doc=QJsonDocument::fromBinaryData(req->body());

    QJsonObject recv_obj=doc.object();//这是接收到的json对象

    QJsonObject resp_obj; //返回json对象

    resp_obj.insert("man_num",4);

    resp_obj.insert("time", "20150601113432");

    QByteArray data = QJsonDocument(resp_obj).toJson(QJsonDocument::Compact);

    resp->setHeader("Content-Type", "text/html");

    resp->setHeader("Content-Length", QString::number(data.length()));

    resp->writeHead(200);

    resp->end(data);

    resp->flush();

    req->deleteLater();

    resp->deleteLater();

    qDebug() <<"handleRequest end";

}

void QHttpServer::sockDisConnectSlot(int handle,const QString & ip, quint16 prot,QThread * th)

{

    qDebug() << "QHttpServer:sockDisConnectSlot,ThreadId:"<<QThread::currentThreadId()  ;

    qDebug() << "QHttpServer m_ClientList size:"<<m_ClientList->size()  ;
    qDebug() << "QHttpServer m_ClientList:remove:"<<handle  ;

    m_ClientList->remove(handle);//连接管理中移除断开连接的socket

    ThreadHandle::getClass().removeThread(th); //告诉线程管理类那个线程里的连接断开了,释放数量

    qDebug() << "QHttpServer m_ClientList size:"<<m_ClientList->size()  ;

}
