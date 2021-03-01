#include "ipex.h"

IpEx::IpEx()
{

}

IpEx::~IpEx()
{

}

//transfer domain name to ip, if is ip, return directly
QString IpEx::getDomainIp(const QString &strDomain)
{
    QString strIp = "";
    if(strDomain.isEmpty())
    {
        return strIp;
    }
    if(strDomain.indexOf(QRegExp("^[0-9]{1,3}.[0-9]{1,3}.[0-9]{1,3}.[0-9]{1,3}$")) >= 0)
    {
        return strDomain;
    }

    //domain==>ip, this will take a minutes, dependance of the network
    QHostInfo info = QHostInfo::fromName(strDomain);

    //get one ip
    QList<QHostAddress> lstHost = info.addresses();
    if(lstHost.length() > 0)
    {
        strIp = lstHost.at(0).toString();
    }

    return strIp;
}
