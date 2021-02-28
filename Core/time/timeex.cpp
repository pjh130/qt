#include "timeex.h"

TimeEx::TimeEx()
{

}

TimeEx::~TimeEx()
{

}

void TimeEx::blockTime(qint64 timeout)
{
    QEventLoop loop;
    QTimer::singleShot(timeout, &loop, SLOT(loop.exit()));
    loop.exec();
}

//返回当前时间字符串：yyyyMMdd
QString TimeEx::YYYYMMDD()
{
    return QDateTime::currentDateTime().toString("yyyyMMdd");
}

//返回当前时间字符串：yyyy-MM-dd
QString TimeEx::YYYY_MM_DD()
{
    return QDateTime::currentDateTime().toString("yyyy-MM-dd");
}

//返回当前时间字符串：yyyy-MM-dd HH:mm:ss.zzz
QString TimeEx::YYYY_MM_DD_HH_MM_SS_ZZZ()
{
    return QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss.zzz");
}

//返回当前时间字符串：yyyy-MM-dd HH:mm:ss
QString TimeEx::YYYY_MM_DD_HH_MM_SS()
{
    return QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss");
}

QDateTime TimeEx::toDateTime(const QString& text)
{
    QDateTime ret = QDateTime();
    switch(text.length())
    {
    case 23:
        ret.fromString(text, "yyyy-MM-dd HH:mm:ss.zzz");
        break;
    case 19:
        ret.fromString(text, "yyyy-MM-dd HH:mm:ss");
        break;
    case 16:
        ret.fromString(text, "yyyy-MM-dd HH:mm");
        break;
    case 14:
        ret.fromString(text, "yyyyMMddHHmmss");
        break;
    case 10:
        ret.fromString(text, "yyyy-MM-dd");
        break;
    case  8:
        ret.fromString(text, "HH:mm:ss");
        break;
    case  7:
        ret.fromString(text, "yyyy/MM");
        break;
    case  6:
        ret.fromString(text, "HHmmss");
        break;
    case  5:
        if ( text.at(2) == '/'
          || text.at(2) == '-' )
        {
            ret.fromString(text, "MM/dd");
        }else
        if ( text.at(2) == ':' )
        {
            ret.fromString(text, "HH:mm");
        }
        break;
    case  4:
        ret.fromString(text, "yyyy");
        break;
    case  2:
        ret.fromString(text, "dd");
        break;
    case  1:
        ret.fromString(text, "d");
        break;
    }
    return ret;
}

QDateTime TimeEx::toDateTime(double timeDouble)
{
    int    days    = int(timeDouble);
    double seconds = timeDouble - days;

    //const qint64 OF_JULIAN_DAY = 2415019;
    QDate date = QDate::fromJulianDay(JULIAN_DAY + days);
    QTime time(0, 0, 0, 0);
    time = time.addSecs(seconds * 86400.0);
    return QDateTime(date, time);
}

