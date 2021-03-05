#include "networkaccessmanagerex.h"

NetworkAccessManagerEx::NetworkAccessManagerEx()
{
    //注册自定义的信号槽参数
    qRegisterMetaType<REQUEST_ST>("REQUEST_ST");
    qRegisterMetaType<REPLY_ST>("REPLY_ST");

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

QByteArray NetworkAccessManagerEx::RequestBlock(const REQUEST_ST request, QString &strError)
{
    return dealRequestBlock(request, strError);
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

QByteArray NetworkAccessManagerEx::dealRequestBlock(const REQUEST_ST &request, QString &strError)
{
    QByteArray byData;
    switch (request.method) {
    case REQUEST_METHOD_HEAD:
        byData = dealRequestHeadBlock(request, strError);
        break;
    case REQUEST_METHOD_GET:
        byData = dealRequestGetBlock(request, strError);
        break;
    case REQUEST_METHOD_POST:
        byData = dealRequestPostBlock(request, strError);
        break;
    case REQUEST_METHOD_DELETE:
        byData = dealRequestDeleteBlock(request, strError);
        break;
    case REQUEST_METHOD_OPTIONS:
        byData = dealRequestOptionsBlock(request, strError);
        break;
    case REQUEST_METHOD_PUT:
        byData = dealRequestPutBlock(request, strError);
        break;
    case REQUEST_METHOD_PATCH:
        byData = dealRequestPatchBlock(request, strError);
        break;
    case REQUEST_METHOD_TRACE:
        byData = dealRequestTraceBlock(request, strError);
        break;
    case REQUEST_METHOD_CONNECT:
        byData = dealRequestConnectBlock(request, strError);
        break;
    default:
        break;
    }

    return byData;
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

QByteArray NetworkAccessManagerEx::dealRequestHeadBlock(const REQUEST_ST &request, QString &strError)
{
    QByteArray byData;
    QNetworkRequest req(request.strUrl);
    QMapIterator<QByteArray, QByteArray> i(request.map);
    while (i.hasNext()) {
        i.next();
        req.setRawHeader(i.key(), i.value());
    }

    QNetworkAccessManager manager;
    QNetworkReply *reply = manager.head(req);

    QEventLoop loop;
    connect(reply, SIGNAL(finished()), &loop, SLOT(quit()));
    loop.exec();

    //判断是否正常执行
    if (QNetworkReply::NoError != reply->error())
    {
        strError = reply->errorString();
    } else {
        byData = reply->readAll();
    }
    reply->close();
    reply->deleteLater();

    return byData;
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

QByteArray NetworkAccessManagerEx::dealRequestGetBlock(const REQUEST_ST &request, QString &strError)
{
    QByteArray byData;
    QNetworkRequest req(request.strUrl);
    QMapIterator<QByteArray, QByteArray> i(request.map);
    while (i.hasNext()) {
        i.next();
        req.setRawHeader(i.key(), i.value());
    }

    QNetworkAccessManager manager;
    QNetworkReply *reply = manager.get(req);

    QEventLoop loop;
    connect(reply, SIGNAL(finished()), &loop, SLOT(quit()));
    loop.exec();

    //判断是否正常执行
    if (QNetworkReply::NoError != reply->error())
    {
        strError = reply->errorString();
    } else {
        byData = reply->readAll();
    }
    reply->close();
    reply->deleteLater();

    return byData;
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

QByteArray NetworkAccessManagerEx::dealRequestPostBlock(const REQUEST_ST &request, QString &strError)
{
    QByteArray byData;
    QNetworkRequest req(request.strUrl);
    QMapIterator<QByteArray, QByteArray> i(request.map);
    while (i.hasNext()) {
        i.next();
        req.setRawHeader(i.key(), i.value());
    }

    QNetworkAccessManager manager;
    QNetworkReply *reply = manager.post(req, request.byData);

    QEventLoop loop;
    connect(reply, SIGNAL(finished()), &loop, SLOT(quit()));
    loop.exec();

    //判断是否正常执行
    if (QNetworkReply::NoError != reply->error())
    {
        strError = reply->errorString();
    } else {
        byData = reply->readAll();
    }
    reply->close();
    reply->deleteLater();

    return byData;
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

QByteArray NetworkAccessManagerEx::dealRequestDeleteBlock(const REQUEST_ST &request, QString &strError)
{
    QByteArray byData;
    QNetworkRequest req(request.strUrl);
    QMapIterator<QByteArray, QByteArray> i(request.map);
    while (i.hasNext()) {
        i.next();
        req.setRawHeader(i.key(), i.value());
    }

    QNetworkAccessManager manager;
    QNetworkReply *reply = manager.deleteResource(req);

    QEventLoop loop;
    connect(reply, SIGNAL(finished()), &loop, SLOT(quit()));
    loop.exec();

    //判断是否正常执行
    if (QNetworkReply::NoError != reply->error())
    {
        strError = reply->errorString();
    } else {
        byData = reply->readAll();
    }
    reply->close();
    reply->deleteLater();

    return byData;
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

QByteArray NetworkAccessManagerEx::dealRequestOptionsBlock(const REQUEST_ST &request, QString &strError)
{
    QByteArray byData;
    strError = "This request type unsupport now!";
    return byData;
}

void NetworkAccessManagerEx::dealRequestOptions(const REQUEST_ST &request)
{

}

QByteArray NetworkAccessManagerEx::dealRequestPutBlock(const REQUEST_ST &request, QString &strError)
{
    QByteArray byData;
    QNetworkRequest req(request.strUrl);
    QMapIterator<QByteArray, QByteArray> i(request.map);
    while (i.hasNext()) {
        i.next();
        req.setRawHeader(i.key(), i.value());
    }

    QNetworkAccessManager manager;
    QNetworkReply *reply = manager.put(req, request.byData);

    QEventLoop loop;
    connect(reply, SIGNAL(finished()), &loop, SLOT(quit()));
    loop.exec();

    //判断是否正常执行
    if (QNetworkReply::NoError != reply->error())
    {
        strError = reply->errorString();
    } else {
        byData = reply->readAll();
    }
    reply->close();
    reply->deleteLater();

    return byData;
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

QByteArray NetworkAccessManagerEx::dealRequestPatchBlock(const REQUEST_ST &request, QString &strError)
{
    QByteArray byData;
    strError = "This request type unsupport now!";
    return byData;
}

void NetworkAccessManagerEx::dealRequestPatch(const REQUEST_ST &request)
{

}

QByteArray NetworkAccessManagerEx::dealRequestTraceBlock(const REQUEST_ST &request, QString &strError)
{
    QByteArray byData;
    strError = "This request type unsupport now!";
    return byData;
}

void NetworkAccessManagerEx::dealRequestTrace(const REQUEST_ST &request)
{

}

QByteArray NetworkAccessManagerEx::dealRequestConnectBlock(const REQUEST_ST &request, QString &strError)
{
    QByteArray byData;
    strError = "This request type unsupport now!";
    return byData;
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
        return;
    }

    //旧数据(因为不知道数据缓存是否能一次读完)
    QByteArray old = m_buff.value(strTask);
    QByteArray arr = old + reply->readAll();

    m_buff.insert(strTask, arr);
}

void NetworkAccessManagerEx::slotError(QNetworkReply::NetworkError err)
{

}

void NetworkAccessManagerEx::slotReplyFinished(QNetworkReply *reply)
{
    REPLY_ST st;
    //查询链表中是否存在数据
    if(m_reply.contains(reply))
    {
        st.strTask = m_reply.value(reply);
//        QString str = "Find [" + st.strTask + "] network result";

        //旧数据
        QByteArray old = m_buff.value(st.strTask);
        QByteArray newdata = reply->readAll();
        st.byData = old + newdata;

        //删除链表数据
        m_reply.remove(reply);
        m_buff.remove(st.strTask);

        if (reply->error() != QNetworkReply::NoError)
        {
            st.bOk = false;
            st.strError = reply->errorString().toUtf8();
        } else {
            st.bOk = true;
        }

        emit workResult(st);

    } else {
    }

    reply->close();
    reply->deleteLater();
}
