#ifndef TCPTHREAD_H
#define TCPTHREAD_H

#include <QThread>
#include <QTcpSocket>
#include <QDebug>
#include <QtNetwork>

class TcpThread : public QThread
{
    Q_OBJECT
public:
   explicit TcpThread(qintptr handle, QObject *parent = 0);
    ~TcpThread();

public:
    void run();

signals:
    void sigError(QTcpSocket::SocketError socketError);
    void sigBytesArrived(qint64,qint32,int);

private slots:
    void readData();
    void errorString(QAbstractSocket::SocketError);

private:
    qintptr m_handle;

    QTcpSocket *m_pTcp;
    QByteArray m_byData;
};

#endif // TCPTHREAD_H
