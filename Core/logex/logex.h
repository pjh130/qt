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
#include "email.h"

//日志等级
typedef enum {
    LEVEL_PRINTF,
    LEVEL_LOG,
    LEVEL_EMAIL,
    LEVEL_SMS
}LOG_LEVEL_EN;

typedef struct {

}INI_SMS_ST;

typedef struct
{
    QString strLogDir; //日志的存放目录
    int i64MaxSize;
    LOG_LEVEL_EN level;

    EMAIL_TO_ST email;
    INI_SMS_ST sms;
}INI_LOG_ST;

//默认的日志大小
#define LOG_MAX_SIZE 1024*1024*300
//默认的一条日志内容长度
#define LOG_ONE_MAX_LENGTH 100

class LogEx
{
public:
    explicit LogEx();
    ~LogEx();

    static LogEx & getClass(); //返回对象引用，是单例类
    void initClass(INI_LOG_ST init);
    //常规日志接口
    void writeLog(QString strLog, LOG_LEVEL_EN level = LEVEL_PRINTF);
    //自定义的日志接口
    void customLog(QtMsgType type, const QMessageLogContext & context,
                              const QString & msg);

private:
    void autoInit();
    void iniLogDir(QString strDir);

    void levelPrintf(QString strLog);
    void levelLog(QString strLog);
    void levelEmail(QString strLog); //具体实现还需要完善
    void levelSms(QString strLog);   //具体实现还需要完善

signals:

public slots:

private:
    QString m_strLogSave;
    QString m_strLogName;
    QFile *m_pFile;
    bool m_bInit;
    QMutex m_mutx;
    INI_LOG_ST m_init;
};

#endif // LOGEX_H
