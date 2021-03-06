#ifndef NETWORKACCESSMANAGEREX_H
#define NETWORKACCESSMANAGEREX_H

#include <QThread>
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkReply>
#include <QtNetwork/QNetworkRequest>
#include <QUrl>
#include <QTimer>
#include <QMap>
#include <QMutex>
#include <QUuid>
#include <QEventLoop>

typedef enum
{
    REQUEST_METHOD_HEAD,
    REQUEST_METHOD_GET,
    REQUEST_METHOD_POST,
    REQUEST_METHOD_DELETE,
    REQUEST_METHOD_OPTIONS,
    REQUEST_METHOD_PUT,
    REQUEST_METHOD_PATCH,
    REQUEST_METHOD_TRACE,
    REQUEST_METHOD_CONNECT,
} REQUEST_METHOD_EN;

typedef struct
{
    REQUEST_METHOD_EN method;
    QString strTask;
    QString strUrl;
    QByteArray byData;
    QMap<QByteArray, QByteArray> map;
}REQUEST_ST;

typedef struct
{
    bool  bOk;
    QString strTask;
    QString strError;
    QByteArray byData;
}REPLY_ST;

class NetworkAccessManagerEx : public QThread
{
    Q_OBJECT

public:
    NetworkAccessManagerEx();
    ~NetworkAccessManagerEx();

    //阻塞的方式执行http请求,如果返回值为空，则strError里边会有错误信息
    static void RequestBlock(const REQUEST_ST &request, REPLY_ST &st);

public slots:
    void slotStart();
    void slotWork();
    void slotAddWork(REQUEST_ST request);

    //网络收发数据相关
    void slotReadyRead();
    void slotError(QNetworkReply::NetworkError err);
    void slotReplyFinished(QNetworkReply *reply);

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

    void workFinished();
    void workStart();

protected:

private:
    QTimer *m_timer;
    QMutex m_lock;
    QNetworkAccessManager *m_manager;
    QMap<QNetworkReply*, QString> m_reply;

    QList<REQUEST_ST> m_task;
    QMap<QString, QByteArray> m_buff;
};

#endif // NETWORKACCESSMANAGEREX_H
