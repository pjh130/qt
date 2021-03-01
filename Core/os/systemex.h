#ifndef SYSTEMEX_H
#define SYSTEMEX_H

#include <QtCore>
#include <QHostInfo>
#ifdef Q_OS_WIN
#include <Windows.h>
#include <Psapi.h>
#else
#include <unistd.h>
#include <stdlib.h>
#endif

class SystemEx
{
public:
    SystemEx();
    ~SystemEx();

    /// @brief 取操作系统名称，支持Windows和Linux
    /// @note Windows从注册表中获取,Linux从依次从/etc下的os-release
    ///       lsb-release, *-release文件获取
    static QString systemName();
    static QString hostName();

    static bool isProcessRunningByPid(long lPid, QString &strErrMsg,
                               bool bGetImageFile=false, PWCHAR pImageFileBuf=0, uint *puiBufSize=0);
    static bool isProcessRunningByFilename(QString strFilename, QString &strErrMsg,
                                    QList<qint64> &lstPid, bool bGetAllPids=false);
    static bool killProcessByPid(qint64 i64Pid);
    static bool isProcessRunningByAppName(QString strAppName, QString &strErrMsg,  QList<qint64> &lstPid, bool bGetAllPids/*=false*/);
    static bool killProcessByAppName(const QString &strFilename, QString &strErrMsg, bool bKillAll=true);
    static bool killProcessByFilename(const QString &strFilename, QString &strErrMsg, bool bKillAll=true);
};

#endif // SYSTEMEX_H
