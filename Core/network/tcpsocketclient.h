#ifndef TCPSOCKETCLIENT_H
#define TCPSOCKETCLIENT_H

#include <QThread>
#include <QTcpSocket>
#include <QQueue>
#include <QHostAddress>
#include <QEventLoop>
#include <QTimer>
#include "netpublic.h"
#include "tcpsocketthread.h"

class TcpSocketClient : public TcpSocketThread
{
    Q_OBJECT
public:
    TcpSocketClient(const QString &strIp, const quint16 port, QObject *parent = 0);
    ~TcpSocketClient();

protected:
    void run();

public slots:

signals:

public slots:

protected slots:

private:
    QString m_strIpSer;
    quint16 m_portSer;

};

#endif // TCPSOCKETCLIENT_H
