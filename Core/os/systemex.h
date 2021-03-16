#ifndef SYSTEMEX_H
#define SYSTEMEX_H

#include <QtCore>
#include <QProcess>
#include <QHostInfo>
#include <QStorageInfo>
#ifdef Q_OS_WIN
#include <Windows.h>
#include <Psapi.h>
#else
#include <unistd.h>
#include <stdlib.h>
#endif
#include <QDesktopServices>

class SystemEx
{
public:
    SystemEx();
    ~SystemEx();

    //获取系统变量的值
    static QString getEnvironmentValue(const QString &strKey);
    static bool openExplorer(const QString &path);

    /// @brief 取操作系统名称，支持Windows和Linux
    /// @note Windows从注册表中获取,Linux从依次从/etc下的os-release
    ///       lsb-release, *-release文件获取
    static QString systemName();
    static QString hostName();
    static bool setPowerAutoStart(const QString &strPath, const bool &bStart = true);

    //磁盘空间相关
    static quint64 getDiskSpace(const QString &driver);  //磁盘总空间
    static quint64 getDiskFreeSpace(const QString &driver); //磁盘剩余空间

    //获取系统硬件信息
    static QString getWMIC(const QString &cmd);
    static QString getCpuName();
    static QString getCpuId();
    static QString getDiskNum();

    //系统进程相关
    static bool isProcessRunningByPid(long lPid, QString &strErrMsg,
                               bool bGetImageFile=false, PWCHAR pImageFileBuf=0, uint *puiBufSize=0);
    static bool isProcessRunningByFilename(QString strFilename, QString &strErrMsg,
                                    QList<qint64> &lstPid, bool bGetAllPids=false);
    static bool killProcessByPid(qint64 i64Pid);
    static bool isProcessRunningByAppName(QString strAppName, QString &strErrMsg,  QList<qint64> &lstPid, bool bGetAllPids/*=false*/);
    static bool killProcessByAppName(const QString &strFilename, QString &strErrMsg, bool bKillAll=true);
    static bool killProcessByFilename(const QString &strFilename, QString &strErrMsg, bool bKillAll=true);
    static bool isAppInstanceRunning(QString strMtxName, QString strAppFile);
};

#endif // SYSTEMEX_H
