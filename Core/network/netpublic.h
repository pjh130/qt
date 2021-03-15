#ifndef NETPUBLIC_H
#define NETPUBLIC_H

#include <QtCore>

typedef struct
{
    qintptr socketID;
    QString strKey;
    QByteArray byData;
}SEND_DATA_ST;

class NetPublic
{
public:
    NetPublic();
};

#endif // NETPUBLIC_H
