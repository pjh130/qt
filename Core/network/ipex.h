#ifndef IPEX_H
#define IPEX_H
#include <QtCore>
#include <QtNetwork>

class IpEx
{
public:
    IpEx();
    ~IpEx();

    //获取域名的ip地址
    QString getDomainIp(const QString &strDomain);
};

#endif // IPEX_H
