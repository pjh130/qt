#ifndef NETPUBLIC_H
#define NETPUBLIC_H

#include <QtCore>

//==========================HTTP 相关==========================
//http请求的类型
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

//http请求的数据
typedef struct
{
    REQUEST_METHOD_EN method;
    QString strTask;
    QString strUrl;
    QByteArray byData;
    QMap<QByteArray, QByteArray> map;
}REQUEST_ST;

//http请求的返回消息
typedef struct
{
    bool  bOk;
    QString strTask;
    QString strError;
    QByteArray byData;
}REPLY_ST;
//==========================HTTP 相关==========================


//==========================TCP 相关==========================
//tcp发送的数据
typedef struct
{
    qintptr socketID;
    QString strKey;
    QByteArray byData;
}SEND_DATA_ST;
//==========================TCP 相关==========================

class NetPublic
{
public:
    NetPublic();
};

#endif // NETPUBLIC_H
