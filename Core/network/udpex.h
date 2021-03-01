#ifndef UDPEX_H
#define UDPEX_H
/*
    【注意：】代码是照抄原作者，仅仅是个人使用，感谢原作者
    Tianchi C++ library for Qt (open source)
    天池共享源码库
    版权所有 (C) 天池共享源码库开发组
*/

#include <QtNetwork>

class UdpEx : public QUdpSocket
{
    Q_OBJECT
    typedef QUdpSocket inherited;
public:
    UdpEx();
    virtual ~UdpEx();

    int         start(int Port);
    void        stop();

    /// @brief 向指定的服务器和端口发送字符集
    bool        sendMessage(QHostAddress host, int port, QByteArray S);
    /// @brief 向指定的服务器和端口发送字符串
    inline bool sendMessage(QHostAddress host, int port, QString S)
                           { return sendMessage(host, port, S.toUtf8()); }
    /// @brief 向指定的端口发送广播字符集
    void        sendBroadcast(int port, QByteArray S);
    /// @brief 向指定的端口发送广播字符串
    inline void sendBroadcast(int port, QString S)
                             { return sendBroadcast(port, S.toUtf8()); }

    /// @brief 设置回调方法，优先于 signals 的接收方式
    inline void setRecvMethod(QObject* recvObject, QByteArray recvMethod)
                             { m_recvObject = recvObject; m_recvMethod = recvMethod; }

Q_SIGNALS:
    /// @brief 设置信号接收槽，只有回调方法未设置时才有效
    void recvMessage(QHostAddress client, QByteArray datagram);

protected slots:
    void udpRecv();

protected:
    QObject*    m_recvObject;
    QByteArray  m_recvMethod;
};

#endif // UDPEX_H
