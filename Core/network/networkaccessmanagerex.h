#ifndef NETWORKACCESSMANAGEREX_H
#define NETWORKACCESSMANAGEREX_H

#include <QThread>
#include <QCoreApplication>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QUrl>
#include <QTimer>
#include <QMap>
#include <QMutex>
#include <QUuid>
#include <QEventLoop>
#include "netpublic.h"

class NetworkAccessManagerEx : public QThread
{
    Q_OBJECT

public:
    NetworkAccessManagerEx();
    ~NetworkAccessManagerEx();

    //阻塞的方式执行http请求,如果返回值为空，则strError里边会有错误信息
    static void RequestBlock(const REQUEST_ST &request, REPLY_ST &st);

protected:
    void quitThread();
    void run();

public slots:
//    void slotStart();
    void slotWork();
    void slotWorkBlock();
    void slotAddWork(REQUEST_ST request);

    //网络收发数据相关
    void slotReadyRead();
    void slotError(QNetworkReply::NetworkError err);
    void slotReplyFinished(QNetworkReply *reply);
    void slotQuit();

private:
    //信号槽的方式请求
    void dealRequest(const REQUEST_ST &request);
    void dealRequestHead(const REQUEST_ST &request);
    void dealRequestGet(const REQUEST_ST &request);
    void dealRequestPost(const REQUEST_ST &request);
    void dealRequestDelete(const REQUEST_ST &request);
    void dealRequestOptions(const REQUEST_ST &request);
    void dealRequestPut(const REQUEST_ST &request);
    void dealRequestPatch(const REQUEST_ST &request);
    void dealRequestTrace(const REQUEST_ST &request);
    void dealRequestConnect(const REQUEST_ST &request);

    //阻塞的方式请求
    static void dealRequestBlock(const REQUEST_ST &request, REPLY_ST &st);
    static void dealRequestHeadBlock(const REQUEST_ST &request, REPLY_ST &st);
    static void dealRequestGetBlock(const REQUEST_ST &request, REPLY_ST &st);
    static void dealRequestPostBlock(const REQUEST_ST &request, REPLY_ST &st);
    static void dealRequestDeleteBlock(const REQUEST_ST &request, REPLY_ST &st);
    static void dealRequestOptionsBlock(const REQUEST_ST &request, REPLY_ST &st);
    static void dealRequestPutBlock(const REQUEST_ST &request, REPLY_ST &st);
    static void dealRequestPatchBlock(const REQUEST_ST &request, REPLY_ST &st);
    static void dealRequestTraceBlock(const REQUEST_ST &request, REPLY_ST &st);
    static void dealRequestConnectBlock(const REQUEST_ST &request, REPLY_ST &st);

signals:
    void workResult(REPLY_ST st);

//    void workFinished();
    void workStart();

protected:

private:
    bool m_bQuit;
    QTimer *m_timer;
    QMutex m_lock;
    QNetworkAccessManager *m_manager;
    QMap<QNetworkReply*, QString> m_reply;

    QList<REQUEST_ST> m_task;
    QMap<QString, QByteArray> m_buff;
};

#endif // NETWORKACCESSMANAGEREX_H
