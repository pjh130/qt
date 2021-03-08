#ifndef TIMEEX_H
#define TIMEEX_H
#include <QtCore>
#include <QDateTime>
#include <QElapsedTimer>
#include <QEventLoop>
#include <QTimer>

class TimeEx
{
public:
    TimeEx();
    ~TimeEx();

    //阻塞一段时间
    static void blockTime(const qint64 &timeout);

    //返回当前时间字符串：yyyyMMdd
    static QString YYYYMMDD();
    //返回当前时间字符串：yyyy-MM-dd
    static QString YYYY_MM_DD();
    //返回当前时间字符串：yyyy-MM-dd HH:mm:ss.zzz
    static QString YYYY_MM_DD_HH_MM_SS_ZZZ();
    //返回当前时间字符串：yyyy-MM-dd HH:mm:ss
    static QString YYYY_MM_DD_HH_MM_SS();

    const static qint64 JULIAN_DAY = 2415019;
    /// @brief 转换字符串为日期时间
    static QDateTime toDateTime(const QString &text);
    /// @brief 转换数据为日期时间
    static QDateTime toDateTime(const double &timeDouble);
};

#endif // TIMEEX_H
