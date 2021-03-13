#include "timeex.h"

TimeEx::TimeEx()
{

}

TimeEx::~TimeEx()
{

}

void TimeEx::blockTime(const qint64 &timeout)
{
    QEventLoop loop;
    QTimer::singleShot(timeout, &loop, SLOT(quit()));
    loop.exec();
}

QString TimeEx::time2humanReadable(const QDateTime &time)
{
    return time2humanReadable(time, "yy-MM-dd");
}

QString TimeEx::time2humanReadable(const QDateTime &time, const QString &formate)
{
    QDateTime t(QDateTime::currentDateTime());
    int nElapseSecs = time.secsTo(t);
    int nElapseDays = time.daysTo(t);

    if (nElapseDays == 1) {
        return QObject::tr("Yesterday");
    } else if (nElapseDays == 2) {
        return QObject::tr("The day before yesterday");
    } else if (nElapseDays > 2) {
        return time.toString(formate);
    }

    if (nElapseSecs < 60) {
        // less than 1 minutes: "just now"
        return QObject::tr("Just now");

    } else if (nElapseSecs >= 60 && nElapseSecs < 60 * 2) {
        // 1 minute: "1 minute ago"
        return QObject::tr("1 minute ago");

    } else if (nElapseSecs >= 120 && nElapseSecs < 60 * 60) {
        // 2-60 minutes: "x minutes ago"
        QString str = QObject::tr("%1 minutes ago");
        return str.arg(nElapseSecs/60);

    } else if (nElapseSecs >= 60 * 60 && nElapseSecs < 60 * 60 * 2) {
        // 1 hour: "1 hour ago"
        return QObject::tr("1 hour ago");

    } else if (nElapseSecs >= 60 * 60 * 2 && nElapseSecs < 60 * 60 * 24) {
        // 2-24 hours: "x hours ago"
        QString str = QObject::tr("%1 hours ago");
        return str.arg(nElapseSecs/60/60);
    }

    return QString("Error");
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

QDateTime TimeEx::toDateTime(const QString &text)
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

QDateTime TimeEx::toDateTime(const double &timeDouble)
{
    int    days    = int(timeDouble);
    double seconds = timeDouble - days;

    //const qint64 OF_JULIAN_DAY = 2415019;
    QDate date = QDate::fromJulianDay(JULIAN_DAY + days);
    QTime time(0, 0, 0, 0);
    time = time.addSecs(seconds * 86400.0);
    return QDateTime(date, time);
}

