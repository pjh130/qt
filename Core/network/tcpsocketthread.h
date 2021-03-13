#ifndef TCPSOCKETTHREAD_H
#define TCPSOCKETTHREAD_H

#include <QThread>
#include <QTcpSocket>
#include <QQueue>
#include <QHostAddress>

class TcpSocketThread : public QThread
{
    Q_OBJECT
public:
    TcpSocketThread();
    ~TcpSocketThread();

protected:
    void closeSockect();

public slots:

signals:
    //发送新用户连接信息
    void connectClient(const int , const QString & ,const quint16 );

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
    void slotStartSocket(qintptr socketDescriptor); //开始工作

protected slots:
    void slotReadData();//接收数据

private:
    QTcpSocket *m_sockect;

    qintptr m_socketID;
    QString m_strIp;
    quint16 m_port;
    QMetaObject::Connection dis;
};

#endif // TCPSOCKETTHREAD_H
