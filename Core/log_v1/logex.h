#ifndef LOGEX_H
#define LOGEX_H

#include <QObject>
#include <QFile>
#include <QFileInfo>
#include <QMutex>
#include <QDebug>
#include <QDateTime>
#include <QtCore>
#include <QDir>

//日志等级
typedef enum {
    LEVEL_PRINT,
    LEVEL_LOG,
    LEVEL_EMAIL,
    LEVEL_SMS
}LOG_LEVEL_EN;

typedef struct
{
    QString strSave;
    int i64MaxSize;
    LOG_LEVEL_EN level;
}LOG_INI_ST;

class LogEx
{
public:
    explicit LogEx();

    static LogEx & getClass(); //返回对象引用，是单例类
    void initLog(LOG_INI_ST ini);
    void writeLog(QString strLog);

private:
    void autoInit();

    void levelPrint(QString strLog);
    void levelLog(QString strLog);
    void levelEmail(QString strLog);
    void levelSms(QString strLog);

signals:

public slots:

private:
    QString m_strLogDir;
    QString m_strLogName;
    QFile *m_pFile;
    bool m_bInit;
    QMutex m_mutx;
    LOG_INI_ST m_init;
};

#endif // LOGEX_H
