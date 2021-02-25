#include "logex.h"

LogEx::LogEx()
{
    m_pFile = NULL;
    m_bInit = false;
    m_strLogDir = QCoreApplication::applicationDirPath() + "/log";
    QDir dir(m_strLogDir);
    if (!dir.exists())
    {
        dir.mkdir(m_strLogDir);
    }
    m_strLogName = "log.log";
}

LogEx & LogEx::getClass()
{
    static LogEx log;
    return log;
}

void LogEx::autoInit()
{
    m_init.strSave = m_strLogDir + "/" + m_strLogName;
//    m_init.level = LEVEL_PRINT;
    m_init.level = LEVEL_LOG;
    m_init.i64MaxSize = 1024*1024*300;

    qDebug()<<m_init.strSave;

    m_bInit = true;
}

void LogEx::initLog(LOG_INI_ST ini)
{
    m_bInit = true;
}

void LogEx::levelPrint(QString strLog)
{
    qDebug()<<strLog;
}

void LogEx::levelLog(QString strLog)
{
    //日志文件过大就先要备份
    QFileInfo info(m_init.strSave);
//    if (true)
    if (info.size() >= m_init.i64MaxSize)
    {
        QString strNew = m_strLogDir + "/" + QDateTime::currentDateTime().toString("yyyyMMdd-hhmmss") + "-" + m_strLogName;
        QFile::rename(m_init.strSave, strNew);
    }

    QFile file(m_init.strSave);
    if (!file.open(QIODevice::Append))
    {
        return;
    }
    file.write(strLog.toUtf8());
    file.close();
}

void LogEx::levelEmail(QString strLog)
{

}

void LogEx::levelSms(QString strLog)
{

}

void LogEx::writeLog(QString strLog)
{
    m_mutx.lock();

    //如果配有初始化日志
    if(!m_bInit)
    {
        autoInit();
    }

    //添加日志打印时间
    QString strWrite = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss") + "  " + strLog + "\r\n";

    //case的选项是等级递增
    switch(m_init.level) {
        case LEVEL_PRINT:
            levelPrint(strWrite);
            break;
        case LEVEL_LOG:
            levelPrint(strWrite);
            levelLog(strWrite);
            break;
        case LEVEL_EMAIL:
            levelPrint(strWrite);
            levelLog(strWrite);
            levelEmail(strWrite);
            break;
        case LEVEL_SMS:
            levelPrint(strWrite);
            levelLog(strWrite);
            levelEmail(strWrite);
            levelSms(strWrite);
            break;
        default:
        break;
    }

    m_mutx.unlock();
}
