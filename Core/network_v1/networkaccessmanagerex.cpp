#include "networkaccessmanagerex.h"

NetworkAccessManagerEx::NetworkAccessManagerEx()
{
    //注册自定义的信号槽参数
    qRegisterMetaType<REQUEST_ST>("REQUEST_ST");

    m_timer = NULL;
    m_manager = NULL;
}

NetworkAccessManagerEx::~NetworkAccessManagerEx()
{
    if (m_manager != NULL)
    {
        m_manager->deleteLater();
    }

    if (m_timer != NULL)
    {
        m_timer->deleteLater();
    }
}

void NetworkAccessManagerEx::slotStart()
{
    m_manager = new QNetworkAccessManager;

    m_timer = new QTimer;
    connect(m_timer, SIGNAL(timeout()), this, SLOT(slotWork()));
    m_timer->start(100);

    emit workStart();
}

void NetworkAccessManagerEx::slotWork()
{
    m_lock.lock();
    if(m_task.length() <= 0)
    {
        m_lock.unlock();
        return;
    }
    REQUEST_ST stReq = m_task.takeAt(0);
    m_lock.unlock();

    dealRequest(stReq);
}

void NetworkAccessManagerEx::dealRequest(const REQUEST_ST &request)
{
    switch (request.method) {
    case REQUEST_METHOD_HEAD:
        dealRequestHead(request);
        break;
    case REQUEST_METHOD_GET:
        dealRequestGet(request);
        break;
    case REQUEST_METHOD_POST:
        dealRequestPost(request);
        break;
    case REQUEST_METHOD_DELETE:
        dealRequestDelete(request);
        break;
    case REQUEST_METHOD_OPTIONS:
        dealRequestOptions(request);
        break;
    case REQUEST_METHOD_PUT:
        dealRequestPut(request);
        break;
    case REQUEST_METHOD_PATCH:
        dealRequestPatch(request);
        break;
    case REQUEST_METHOD_TRACE:
        dealRequestTrace(request);
        break;
    case REQUEST_METHOD_CONNECT:
        dealRequestConnect(request);
        break;
    default:
        break;
    }
}

void NetworkAccessManagerEx::dealRequestHead(const REQUEST_ST &request)
{
    QNetworkRequest req(request.strUrl);
    QMapIterator<QByteArray, QByteArray> i(request.map);
    while (i.hasNext()) {
        i.next();
        req.setRawHeader(i.key(), i.value());
    }

    QNetworkReply *reply = m_manager->head(req);
    connect(reply, SIGNAL(readyRead()), this, SLOT(slotReadyRead()));
    connect(m_manager, SIGNAL(finished(QNetworkReply*)),
            this, SLOT(slotReplyFinished(QNetworkReply*)));
    m_reply.insert(reply, request.strTask);
}

void NetworkAccessManagerEx::dealRequestGet(const REQUEST_ST &request)
{
    QNetworkRequest req(request.strUrl);
    QMapIterator<QByteArray, QByteArray> i(request.map);
    while (i.hasNext()) {
        i.next();
        req.setRawHeader(i.key(), i.value());
    }

    QNetworkReply *reply = m_manager->get(req);
    connect(reply, SIGNAL(readyRead()), this, SLOT(slotReadyRead()));
    connect(m_manager, SIGNAL(finished(QNetworkReply*)),
            this, SLOT(slotReplyFinished(QNetworkReply*)));
    m_reply.insert(reply, request.strTask);
}

void NetworkAccessManagerEx::dealRequestPost(const REQUEST_ST &request)
{
    QNetworkRequest req(request.strUrl);
    QMapIterator<QByteArray, QByteArray> i(request.map);
    while (i.hasNext()) {
        i.next();
        req.setRawHeader(i.key(), i.value());
    }

    QNetworkReply *reply = m_manager->post(req, request.byData);
    connect(reply, SIGNAL(readyRead()), this, SLOT(slotReadyRead()));
    connect(m_manager, SIGNAL(finished(QNetworkReply*)),
            this, SLOT(slotReplyFinished(QNetworkReply*)));
    m_reply.insert(reply, request.strTask);
}

void NetworkAccessManagerEx::dealRequestDelete(const REQUEST_ST &request)
{
    QNetworkRequest req(request.strUrl);
    QMapIterator<QByteArray, QByteArray> i(request.map);
    while (i.hasNext()) {
        i.next();
        req.setRawHeader(i.key(), i.value());
    }

    QNetworkReply *reply = m_manager->deleteResource(req);
    connect(reply, SIGNAL(readyRead()), this, SLOT(slotReadyRead()));
    connect(m_manager, SIGNAL(finished(QNetworkReply*)),
            this, SLOT(slotReplyFinished(QNetworkReply*)));
    m_reply.insert(reply, request.strTask);
}

void NetworkAccessManagerEx::dealRequestOptions(const REQUEST_ST &request)
{

}

void NetworkAccessManagerEx::dealRequestPut(const REQUEST_ST &request)
{
    QNetworkRequest req(request.strUrl);
    QMapIterator<QByteArray, QByteArray> i(request.map);
    while (i.hasNext()) {
        i.next();
        req.setRawHeader(i.key(), i.value());
    }

    QNetworkReply *reply = m_manager->put(req, request.byData);
    connect(reply, SIGNAL(readyRead()), this, SLOT(slotReadyRead()));
    connect(m_manager, SIGNAL(finished(QNetworkReply*)),
            this, SLOT(slotReplyFinished(QNetworkReply*)));
    m_reply.insert(reply, request.strTask);
}

void NetworkAccessManagerEx::dealRequestPatch(const REQUEST_ST &request)
{

}

void NetworkAccessManagerEx::dealRequestTrace(const REQUEST_ST &request)
{

}

void NetworkAccessManagerEx::dealRequestConnect(const REQUEST_ST &request)
{

}

void NetworkAccessManagerEx::slotAddWork(REQUEST_ST request)
{
    m_lock.lock();
    m_task.append(request);
    m_lock.unlock();
}

//网络收发数据相关
void NetworkAccessManagerEx::slotReadyRead()
{
    QNetworkReply* reply = (QNetworkReply*)sender();

    //查询链表中是否存在数据
    QString strTask;
    if(m_reply.contains(reply))
    {
        strTask = m_reply.value(reply);
    } else {
        qDebug()<<"network result can't find data";
        return;
    }

    //旧数据
    QByteArray old = m_buff.value(strTask);
    QByteArray arr = old + reply->readAll();

    m_buff.insert(strTask, arr);
}

void NetworkAccessManagerEx::slotError(QNetworkReply::NetworkError err)
{

}

void NetworkAccessManagerEx::slotReplyFinished(QNetworkReply *reply)
{
    //查询链表中是否存在数据
    QString strTask;
    if(m_reply.contains(reply))
    {
        strTask = m_reply.value(reply);
        QString str = "Find [" + strTask + "] network result";
        qDebug()<<str;

        //旧数据
        QByteArray old = m_buff.value(strTask);
        QByteArray data = old + reply->readAll();

        //删除链表数据
        m_reply.remove(reply);
        m_buff.remove(strTask);

        bool bOk = true;
        if (reply->error() != QNetworkReply::NoError)
        {
            bOk = false;
            data = reply->errorString().toUtf8();
        }

        emit workResult(bOk, strTask, data);

    } else {
        //        qDebug()<<"network result can't find data";
    }

    //delete reply;
    reply->deleteLater();
}
