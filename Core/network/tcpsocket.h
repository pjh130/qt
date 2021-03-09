#ifndef TCPSOCKET_H
#define TCPSOCKET_H

#include <QTcpSocket>
#include <QQueue>
#include <QFutureWatcher>
#include <QByteArray>
#include <QTime>

class TcpSocket : public QTcpSocket
{
    Q_OBJECT
public:
    explicit TcpSocket(qintptr socketDescriptor, QObject *parent = 0);
    ~TcpSocket();

signals:
    //NOTE:断开连接的用户信息，此信号必须发出！线程管理类根据信号计数的
    void sockDisConnect(const qintptr socketID , const QString &strIp,
                        const quint16 port, QThread *thread);
    //发送数据的结果
    void sendDataRet(const qintptr socketID, const QString &strKey,
                     const bool &bOk, const QString &strError);
    //收到的数据转发出去
    void receiveData(const qintptr socketID, const QByteArray data);

public slots:
    void slotSentData(const qintptr socketID, const QString &strKey, const QByteArray &data);//发送信号的槽
    void disConTcp(const qintptr socketID);

protected slots:
    void slotReadData();//接收数据
protected:
    QFutureWatcher<QByteArray> watcher;
    QQueue<QByteArray> datas;
private:
    qintptr m_socketID;
    QString m_strIp;
    quint16 m_port;
    QMetaObject::Connection dis;
};

#endif // TCPSOCKET_H