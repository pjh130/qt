#include "logex.h"

LogEx::LogEx()
{
    m_pFile = NULL;
    m_bInit = false;
    m_init.strLogDir = QCoreApplication::applicationDirPath() + QDir::separator() + "log";
    m_strLogName = "log.log";

    levelPrintf("Default max log size: " + QString::number( LOG_MAX_SIZE));
}

LogEx::~LogEx()
{
    if (m_pFile)
    {
        m_pFile->close();
        m_pFile->deleteLater();
        m_pFile = NULL;
        levelPrintf("Close file: " + m_strLogSave);
    }
}

LogEx & LogEx::getClass()
{
    static LogEx log;
    return log;
}

void LogEx::customLog(const QtMsgType &type, const QMessageLogContext &context,
                                 const QString &msg)
{
    QString txt;
    switch (type) {
    //调试信息提示
    case QtDebugMsg:
        //        txt = msg;
        txt = QString("Debug: at:%1,%2 on %3; %4").arg(context.file).arg(context.line)
                .arg(context.function).arg(msg);
        break;

        //一般的warning提示
    case QtWarningMsg:
        txt = QString("Warning: at:%1,%2 on %3; %4").arg(context.file).arg(context.line)
                .arg(context.function).arg(msg);
        break;
        //严重错误提示
    case QtCriticalMsg:
        txt = QString("Critical: at:%1,%2 on %3; %4").arg(context.file).arg(context.line)
                .arg(context.function).arg(msg);
        break;
        //致命错误提示
    case QtFatalMsg:
        txt = QString("Fatal: at:%1,%2 on %3; %4").arg(context.file).arg(context.line)
                .arg(context.function).arg(msg);
        abort();
    }

    levelLog(txt);
}

void LogEx::messageHandler(QtMsgType type, const QMessageLogContext& context, const QString &msg)
{
    Q_UNUSED(context);

    //FIXME: useless waning message from qt, ignore it
#ifndef QT_DEBUG
    if (msg.startsWith("libpng warning: iCCP:") || msg.startsWith("QSslSocket: cannot call unresolved"))
        return;
#endif

    if (type == QtWarningMsg && msg.startsWith("Property") && msg.indexOf("has no notify signal") != -1)
        return;

    QString strWrite;
    switch (type) {
    case QtDebugMsg:
        strWrite = QString("[DEBUG] %1").arg(msg.toUtf8().constData());
        break;
#if QT_VERSION >= 0x050500
    case QtInfoMsg:
        strWrite = QString("[INFO] %1").arg(msg.toUtf8().constData());
        break;
#endif
    case QtWarningMsg:
        strWrite = QString("[WARNING]: %1 (%2:%3, %4)").arg(msg.toUtf8().constData()).arg(context.file)
                .arg(context.line).arg(context.function);
        break;
    case QtCriticalMsg:
        strWrite = QString("[CRITICAL]: %1 (%2:%3, %4)").arg(msg.toUtf8().constData()).arg(context.file)
                .arg(context.line).arg(context.function);
        break;
    case QtFatalMsg:
        strWrite = QString("[FATAL]: %1 (%2:%3, %4)").arg(msg.toUtf8().constData()).arg(context.file)
                .arg(context.line).arg(context.function);
        break;
    }

    fprintf(stderr,"%s\n", strWrite.toUtf8().constData());

    levelLog(strWrite);
}

void LogEx::iniLogDir(const QString &strDir)
{
    if (!strDir.isEmpty())
    {
        m_init.strLogDir = strDir;
    } else {
        levelPrintf("Log dir is empty, use default dir: " + m_init.strLogDir);
    }

    QDir dir(m_init.strLogDir);
    if (!dir.exists())
    {
        dir.mkdir(m_init.strLogDir);
    }

    m_strLogSave = m_init.strLogDir + QDir::separator() + m_strLogName;

    levelPrintf("Log save path: " + m_strLogSave);
}

void LogEx::autoInit()
{
    iniLogDir("");

    m_init.level = LEVEL_PRINTF;
    //    m_init.level = LEVEL_LOG;
    m_init.i64MaxSize = LOG_MAX_SIZE;

    m_bInit = true;
}

void LogEx::initClass(INI_LOG_ST init)
{
    iniLogDir(init.strLogDir);

    m_pFile = new QFile(m_strLogSave);
    if (m_pFile->open(QIODevice::Append))
    {

    } else {
        levelPrintf(m_pFile->errorString());
        m_pFile->deleteLater();
        m_pFile = NULL;
    }

    m_init.i64MaxSize = init.i64MaxSize;
    if (m_init.i64MaxSize <= 0)
    {
        m_init.i64MaxSize = LOG_MAX_SIZE;
    }
    m_init.level = init.level;

    //email
    m_init.email.files = init.email.files;
    m_init.email.iPort = init.email.iPort;
    m_init.email.strContent = init.email.strContent;
    m_init.email.strHost = init.email.strHost;
    m_init.email.strPwd = init.email.strPwd;
    m_init.email.strSubject = init.email.strSubject;
    m_init.email.strUser = init.email.strUser;
    m_init.email.strUserName = init.email.strUserName;
    m_init.email.toUsers = init.email.toUsers;

    //SMS

    m_bInit = true;
}

void LogEx::levelPrintf(const QString &strLog)
{
    QString strNew = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss") + "  " + strLog + "\r\n";
    qDebug()<<strNew;
}

void LogEx::levelLog(const QString &strLog)
{
    //日志文件过大就先要备份
    QFileInfo info(m_strLogSave);
    //    if(true)
    if (info.size() >= m_init.i64MaxSize)
    {
        //先关闭文件
        if (m_pFile)
        {
            m_pFile->close();
        }

        //备份日志文件
        QString strNew = m_init.strLogDir + QDir::separator() + QDateTime::currentDateTime().toString("yyyyMMdd-hhmmss") + "-" + m_strLogName;
        QFile::rename(m_strLogSave, strNew);
        levelPrintf("Log is large, need to rename: " + strNew);

        if (m_pFile)
        {
            //重新打开文件
            if (m_pFile->open(QIODevice::Append))
            {

            } else {
                levelPrintf("Failed to open file: " + m_pFile->errorString());
                m_pFile->deleteLater();
                m_pFile = NULL;
            }
        }
    }

    QString strNew = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss") + "  " + strLog + "\r\n";

    //用户自定义了配置文件LOG就不需要每次打开关闭文件
    if (m_pFile)
    {
        m_pFile->write(strNew.toUtf8());
        m_pFile->flush();
    } else {
        QFile file(m_strLogSave);
        if (!file.open(QIODevice::Append))
        {
            levelPrintf("Failed to open file: " + file.errorString());
            return;
        }

        file.write(strNew.toUtf8());
        file.close();
    }
}

void LogEx::levelEmail(const QString &strLog)
{
    m_init.email.strContent = strLog;

    QString str;
    QString strError;
    if (!EmailCore::send(m_init.email, strError))
    {
        str = "Failed to send email: " + strError + "----" + strLog.mid(0,LOG_ONE_MAX_LENGTH);
        levelLog(str);
    } else {
        str = "Success to send email!";
    }

    levelPrintf(str);
}

void LogEx::levelSms(const QString &strLog)
{
    QString str;
    if (false)
    {
        str = "Success to send sms!";
    } else {
        str = "Failed to send sms!----" + strLog.mid(0,LOG_ONE_MAX_LENGTH);
        levelLog(str);
    }

    levelPrintf(str);
}

void LogEx::writeLog(const QString &strLog, const LOG_LEVEL_EN &level)
{
    m_mutx.lock();

    //如果配有初始化日志
    if(!m_bInit)
    {
        autoInit();
    }

    //默认只打印，这个为了多一种灵活的打印接口分支
    LOG_LEVEL_EN enLevel;
    if (level != LEVEL_PRINTF)
    {
        enLevel = level;
    } else {
        enLevel = m_init.level;
    }

    //默认都会在控制台打印出来
    levelPrintf(strLog);

    //找到对应的日志等级
    switch(enLevel) {
    case LEVEL_PRINTF:
        break;
    case LEVEL_LOG:
        levelLog(strLog);
        break;
    case LEVEL_EMAIL:
        levelEmail(strLog);
        break;
    case LEVEL_SMS:
        levelSms(strLog);
        break;
    default:
        break;
    }

    m_mutx.unlock();
}
