#ifndef TCPSERVER_H
#define TCPSERVER_H
#include <QTcpServer>
#include <QHash>
#include "tcpsocket.h"
#include "tcpsocketthread.h"
#include "threadhandle.h"
#include <QUuid>
#include "netpublic.h"


//继承QTCPSERVER以实现多线程TCPscoket的服务器。
//如果socket的信息处理直接处理的话，很多新建的信号和槽是用不到的
class TcpServer : public QTcpServer
{
    Q_OBJECT
public:
    explicit TcpServer(QObject *parent = 0,int numConnections = 10000);
    ~TcpServer();

    void setMaxPendingConnections(int numConnections);//重写设置最大连接数函数
signals:
    void connectClient(const int , const QString & ,const quint16 );//发送新用户连接信息
    void sockDisConnect(int ,QString ,quint16);//断开连接的用户信息
    void sendData(SEND_DATA_ST st);
    void sendDisConnect(int i); //断开特定连接，并释放资源，-1为断开所有。

public slots:
    //在这里处理接收到的数据逻辑
    void slotReceiveData(const qintptr socketID, const QByteArray data);
    //发送数据的结果
    void slotSendDataRet(const qintptr socketID, const QString &strKey,
                     const bool &bOk, const QString &strError);
    void clear(); //断开所有连接，线程计数器请0
protected slots:
    void sockDisConnectSlot(const qintptr socketID , const QString &strIp,
                            const quint16 port, QThread *thread);//断开连接的用户信息

protected:
    void incomingConnection(qintptr socketDescriptor);//覆盖已获取多线程
    void getSockect1(qintptr socketDescriptor);
    void getSockect2(qintptr socketDescriptor);
private:
    QHash<int,TcpSocket *> tcpClient1;//管理连接的map
    QHash<int,TcpSocketThread *> tcpClient2;//管理连接的map
    bool m_bUse_1_or_2;
    int maxConnections;

};

#endif // TCPSERVER_H
