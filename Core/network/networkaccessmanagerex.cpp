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

void NetworkAccessManagerEx::run()
{
    qDebug()<<"NetworkAccessManagerEx::run: "<<QThread::currentThreadId();
    m_manager = new QNetworkAccessManager;
    m_timer = new QTimer;
    //必须加DirectConnection，要不连接的slot在父线程中执行
    connect(m_timer, SIGNAL(timeout()), this, SLOT(slotWork()), Qt::DirectConnection);
    m_timer->start(100);

    emit workStart();
    exec();
}

//void NetworkAccessManagerEx::slotStart()
//{
//    qDebug()<<"NetworkAccessManagerEx::slotStart: "<<QThread::currentThreadId();
//    m_manager = new QNetworkAccessManager;

//    m_timer = new QTimer;
//    connect(m_timer, SIGNAL(timeout()), this, SLOT(slotWork()));
//    m_timer->start(100);

//    emit workStart();
//}

void NetworkAccessManagerEx::RequestBlock(const REQUEST_ST &request, REPLY_ST &st)
{
    st.strTask = request.strTask;
    return dealRequestBlock(request, st);
}

void NetworkAccessManagerEx::slotWorkBlock()
{
    m_lock.lock();
    if(m_task.length() <= 0)
    {
        m_lock.unlock();
        return;
    }
    REQUEST_ST stReq = m_task.takeAt(0);
    m_lock.unlock();

    REPLY_ST st;
    dealRequestBlock(stReq, st);
    emit workResult(st);
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

void NetworkAccessManagerEx::dealRequestBlock(const REQUEST_ST &request, REPLY_ST &st)
{
    switch (request.method) {
    case REQUEST_METHOD_HEAD:
        dealRequestHeadBlock(request, st);
        break;
    case REQUEST_METHOD_GET:
        dealRequestGetBlock(request, st);
        break;
    case REQUEST_METHOD_POST:
        dealRequestPostBlock(request, st);
        break;
    case REQUEST_METHOD_DELETE:
        dealRequestDeleteBlock(request, st);
        break;
    case REQUEST_METHOD_OPTIONS:
        dealRequestOptionsBlock(request, st);
        break;
    case REQUEST_METHOD_PUT:
        dealRequestPutBlock(request, st);
        break;
    case REQUEST_METHOD_PATCH:
        dealRequestPatchBlock(request, st);
        break;
    case REQUEST_METHOD_TRACE:
        dealRequestTraceBlock(request, st);
        break;
    case REQUEST_METHOD_CONNECT:
        dealRequestConnectBlock(request, st);
        break;
    default:
        break;
    }
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

void NetworkAccessManagerEx::dealRequestHeadBlock(const REQUEST_ST &request, REPLY_ST &st)
{
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
        st.bOk = false;
        st.strError = reply->errorString();
    } else {
        st.bOk = true;
        st.byData = reply->readAll();
    }
    reply->close();
    reply->deleteLater();
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
    connect(reply, SIGNAL(readyRead()), this, SLOT(slotReadyRead()), Qt::DirectConnection);
    connect(m_manager, SIGNAL(finished(QNetworkReply*)),
            this, SLOT(slotReplyFinished(QNetworkReply*)), Qt::DirectConnection);
    m_reply.insert(reply, request.strTask);
}

void NetworkAccessManagerEx::dealRequestGetBlock(const REQUEST_ST &request, REPLY_ST &st)
{
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
        st.bOk = false;
        st.strError = reply->errorString();
    } else {
        st.bOk = true;
        st.byData = reply->readAll();
    }
    reply->close();
    reply->deleteLater();
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
    connect(reply, SIGNAL(readyRead()), this, SLOT(slotReadyRead()), Qt::DirectConnection);
    connect(m_manager, SIGNAL(finished(QNetworkReply*)),
            this, SLOT(slotReplyFinished(QNetworkReply*)), Qt::DirectConnection);
    m_reply.insert(reply, request.strTask);
}

void NetworkAccessManagerEx::dealRequestPostBlock(const REQUEST_ST &request, REPLY_ST &st)
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
        st.bOk = false;
        st.strError = reply->errorString();
    } else {
        st.bOk = true;
        st.byData = reply->readAll();
    }
    reply->close();
    reply->deleteLater();

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
    QMetaObject::Connection dis = connect(reply, SIGNAL(readyRead()), this, SLOT(slotReadyRead()), Qt::DirectConnection);
    connect(m_manager, SIGNAL(finished(QNetworkReply*)),
            this, SLOT(slotReplyFinished(QNetworkReply*)), Qt::DirectConnection);
    m_reply.insert(reply, request.strTask);
}

void NetworkAccessManagerEx::dealRequestDeleteBlock(const REQUEST_ST &request, REPLY_ST &st)
{
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
        st.bOk = false;
        st.strError = reply->errorString();
    } else {
        st.bOk = true;
        st.byData = reply->readAll();
    }
    reply->close();
    reply->deleteLater();
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
    connect(reply, SIGNAL(readyRead()), this, SLOT(slotReadyRead()), Qt::DirectConnection);
    connect(m_manager, SIGNAL(finished(QNetworkReply*)),
            this, SLOT(slotReplyFinished(QNetworkReply*)), Qt::DirectConnection);
    m_reply.insert(reply, request.strTask);
}

void NetworkAccessManagerEx::dealRequestOptionsBlock(const REQUEST_ST &request, REPLY_ST &st)
{
    st.bOk = false;
    st.strError = "This request type unsupport now!";
}

void NetworkAccessManagerEx::dealRequestOptions(const REQUEST_ST &request)
{

}

void NetworkAccessManagerEx::dealRequestPutBlock(const REQUEST_ST &request, REPLY_ST &st)
{
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
        st.bOk = false;
        st.strError = reply->errorString();
    } else {
        st.bOk = true;
        st.byData = reply->readAll();
    }
    reply->close();
    reply->deleteLater();
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
    connect(reply, SIGNAL(readyRead()), this, SLOT(slotReadyRead()), Qt::DirectConnection);
    connect(m_manager, SIGNAL(finished(QNetworkReply*)),
            this, SLOT(slotReplyFinished(QNetworkReply*)), Qt::DirectConnection);
    m_reply.insert(reply, request.strTask);
}

void NetworkAccessManagerEx::dealRequestPatchBlock(const REQUEST_ST &request, REPLY_ST &st)
{
    st.bOk = false;
    st.strError = "This request type unsupport now!";
}

void NetworkAccessManagerEx::dealRequestPatch(const REQUEST_ST &request)
{

}

void NetworkAccessManagerEx::dealRequestTraceBlock(const REQUEST_ST &request, REPLY_ST &st)
{
    st.bOk = false;
    st.strError = "This request type unsupport now!";
}

void NetworkAccessManagerEx::dealRequestTrace(const REQUEST_ST &request)
{

}

void NetworkAccessManagerEx::dealRequestConnectBlock(const REQUEST_ST &request, REPLY_ST &st)
{
    st.bOk = false;
    st.strError = "This request type unsupport now!";
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
    qDebug()<<"NetworkAccessManagerEx::slotReplyFinished: "<<QThread::currentThreadId();

    REPLY_ST st;
    //查询链表中是否存在数据
    if(m_reply.contains(reply))
    {
        st.strTask = m_reply.value(reply);
        //        QString str = "Find [" + st.strTask + "] network result";

        //旧数据
        QByteArray old = m_buff.value(st.strTask);

        //删除链表数据
        m_reply.remove(reply);
        m_buff.remove(st.strTask);

        if (reply->error() != QNetworkReply::NoError)
        {
            st.bOk = false;
            st.strError = reply->errorString().toUtf8();
        } else {
            st.bOk = true;
            QByteArray newdata = reply->readAll();
            st.byData = old + newdata;
        }
        emit workResult(st);
    } else {

    }

    reply->close();
    reply->deleteLater();
}
