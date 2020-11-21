#include "qasynhttpsocket.h"

QAsynHttpSocket::QAsynHttpSocket(qintptr socketDescriptor, QObject *parent)
{

}

QAsynHttpSocket::QAsynHttpSocket(qintptr socketDescriptor, QObject *parent) : //构造函数在主线程执行，lambda在子线程

    QTcpSocket(parent),socketID(socketDescriptor),

    m_parser(0),

    m_parserSettings(0),

    m_transmitLen(0),

    m_transmitPos(0)

{

    this->setSocketDescriptor(socketDescriptor);

    m_parser = (http_parser *)malloc(sizeof(http_parser));

    http_parser_init(m_parser, HTTP_REQUEST);

    m_parserSettings = new http_parser_settings();

    m_parserSettings->on_message_begin = doMessageBegin;

    m_parserSettings->on_message_complete = doMessageComplete;

    m_parserSettings->on_header_field = doHeaderField;

    m_parserSettings->on_header_value = doHeaderValue;

    //在HeadersComplete完成时激发newRequest

    m_parserSettings->on_headers_complete = doHeadersComplete;

    m_parserSettings->on_body = doBody;

    m_parserSettings->on_status = doStatus;

    m_parserSettings->on_url = doUrl;

    m_parserSettings->on_chunk_header = doChunkHeader;

    m_parserSettings->on_chunk_complete = doChunkComplete;

    m_parser->data = this;

    connect(this, SIGNAL(readyRead()), this, SLOT(doParseRequest()));

    connect(this, SIGNAL(disconnected()), this, SLOT(doDisconnected()));

    //当所有的字节写完updateWriteCount激发allBytesWritten信号

    connect(this, SIGNAL(bytesWritten(qint64)), this, SLOT(doUpdateWriteCount(qint64)));

    qDebug() << "new connect:"<<socketDescriptor ;

}

void QAsynHttpSocket::doParseRequest()

{

    Q_ASSERT(m_parser);

    qDebug() << "QHttpConnection:parseRequest,ThreadId:"<<QThread::currentThreadId()  ;

    while (this->bytesAvailable()) {

        qDebug() << "readAll,ThreadId:"<<QThread::currentThreadId()  ;

        QByteArray arr = this->readAll();

        qDebug() << "http_parser_execute begin,ThreadId:"<<QThread::currentThreadId()  ;

        http_parser_execute(m_parser, m_parserSettings, arr.constData(), arr.size());



        qDebug() << "http_parser_execute end,ThreadId:"<<QThread::currentThreadId()  ;

    }

}

int QAsynHttpSocket::doMessageComplete(http_parser *parser)

{

    qDebug() << "doMessageComplete" ;

    // TODO: do cleanup and prepare for next request

    QAsynHttpSocket *theConnection = static_cast<QAsynHttpSocket *>(parser->data);

    QHttpRequest* request = new QHttpRequest(theConnection);

    /** set method **/

    request->setMethod(static_cast<QHttpRequest::HttpMethod>(parser->method));

    /** set version **/

    request->setVersion(

                QString("%1.%2").arg(parser->http_major).arg(parser->http_minor));

    /** get parsed url **/

    struct http_parser_url urlInfo;

    int r = http_parser_parse_url(theConnection->m_currentUrl.constData(),

                                  theConnection->m_currentUrl.size(),

                                  parser->method == HTTP_CONNECT, &urlInfo);

    Q_ASSERT(r == 0);

    Q_UNUSED(r);

    request->setUrl(createUrl(theConnection->m_currentUrl.constData(), urlInfo));

    // Insert last remaining header,这个已经在doHeadersComplete中执行

    //theConnection->m_currentHeaders[theConnection->m_currentHeaderField.toLower()] =

    //   theConnection->m_currentHeaderValue;

    request->setHeaders(theConnection->m_currentHeaders);

    /** set client information **/

    request->m_remoteAddress = theConnection->peerAddress().toString();

    request->m_remotePort = theConnection->peerPort();

    qDebug() << "QHttpResponse:new,ThreadId:"<<QThread::currentThreadId()  ;

    QHttpResponse *response = new QHttpResponse(theConnection);

    if (parser->http_major < 1 || parser->http_minor < 1)

        response->m_keepAlive = false;

    Q_EMIT theConnection->newRequest(request, response);

    return 0;

}
