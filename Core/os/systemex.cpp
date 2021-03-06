#include "systemex.h"
#if defined(Q_OS_WIN)
#include <windows.h>
#endif

SystemEx::SystemEx()
{

}

SystemEx::~SystemEx()
{

}

QString SystemEx::getEnvironmentValue(const QString &strKey)
{
    return QProcessEnvironment::systemEnvironment().value(strKey);
}

bool SystemEx::openExplorer(const QString &path)
{
    QFileInfo info(path);
    if (info.isDir()) {
        return QDesktopServices::openUrl(QUrl::fromLocalFile(info.filePath()));
    } else {
        return QDesktopServices::openUrl(QUrl::fromLocalFile(info.path()));
    }
    return false;
}

QString SystemEx::getWMIC(const QString &cmd)
{
    //获取cpu名称：wmic cpu get Name
    //获取cpu核心数：wmic cpu get NumberOfCores
    //获取cpu线程数：wmic cpu get NumberOfLogicalProcessors
    //查询cpu序列号：wmic cpu get processorid
    //查询主板序列号：wmic baseboard get serialnumber
    //查询BIOS序列号：wmic bios get serialnumber
    //查看硬盘：wmic diskdrive get serialnumber
    QProcess p;
    p.start(cmd);
    p.waitForFinished();
    QString result = QString::fromLocal8Bit(p.readAllStandardOutput());
    QStringList list = cmd.split(" ");
    result = result.remove(list.last(), Qt::CaseInsensitive);
    result = result.replace("\r", "");
    result = result.replace("\n", "");
    result = result.simplified();
    return result;
}

QString SystemEx::getCpuName()
{
    return getWMIC("wmic cpu get name");
}

QString SystemEx::getCpuId()
{
    return getWMIC("wmic cpu get processorid");
}

QString SystemEx::getDiskNum()
{
    return getWMIC("wmic diskdrive where index=0 get serialnumber");
}

// return OS's name
QString SystemEx::systemName()
{
    QString ret;
#if defined(Q_OS_WIN)
    const QString RegPath("HKEY_LOCAL_MACHINE\\Software\\Microsoft\\"
            "Windows NT\\CurrentVersion");
    QSettings reg(RegPath, QSettings::NativeFormat);
    ret = reg.value("ProductName").toString();
#endif
#if defined(Q_OS_LINUX)
    if (QFile::exists("/etc/os-release"))
    {
        QSettings ini("/etc/os-release", QSettings::IniFormat);
        ret = ini.value("PRETTY_NAME").toString();
    }
    else if (QFile::exists("/etc/lsb-release"))
    {
        QSettings ini("/etc/lsb-release", QSettings::IniFormat);
        ret = ini.value("DISTRIB_DESCRIPTION").toString();
    }
    else
    {
        QStringList slFile = QDir("/etc/").entryList(
                    QStringList() << "*-release",
                    QDir::Files | QDir::NoSymLinks | QDir::NoDotAndDotDot);
        if (!slFile.isEmpty())
        {
            QFile file("/etc/" + slFile.first());
            if (file.open(QIODevice::ReadOnly | QIODevice::Text))
            {
                QTextStream in(&file);
                ret = in.readLine();
                file.close();
            }
        }
    }
#endif
    return ret;
}

QString SystemEx::hostName()
{
    return QHostInfo::localHostName();
}

bool SystemEx::setPowerAutoStart(const QString &strPath, const bool &bStart)
{
    bool bRet = false;
    if (strPath.isEmpty() || !QFile::exists(strPath))
    {
        return bRet;
    }

#ifdef Q_OS_WIN     //windows platform
    QSettings reg("HKEY_CURRENT_USER\\SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run",
                  QSettings::NativeFormat);
    QString strAppPath = QDir::toNativeSeparators(strPath);
    QString strAppName = QFileInfo(strAppPath).baseName();

    reg.setValue(strAppName, bStart ? strAppPath : "");
#else

#endif

    return true;
}

/*==========================================
//check if the process is running by pid
//
//lPid: the process pid
//strErrMsg: if error occurs, not empty, else is empty
//bGetImageFile: return the process imagefile? default false. if false, ignore pImageFileBuf and uiBufSize
//pImageFileBuf: buffer to save the return ImageFile, if not enought, will truncated and null terminated
//puiBufSize: input==>the size of pImageFileBuf, in bytes; output==>min(imagefileSize,pImageFileBufSize-1) in bytes
//
//author: moyannie
//date: 2011/06/22
//modified:
===========================================*/
bool SystemEx::isProcessRunningByPid(long lPid, QString &strErrMsg,
                                     bool bGetImageFile/*=false*/, PWCHAR pImageFileBuf/*=0*/, uint *puiBufSize/*=0*/)
{
    //check input params
    if(lPid <= 0)
    {
        strErrMsg += "In isProcessRunningByPid(), lPid must large than zero!\n";
        return false;
    }
    if(bGetImageFile)
    {
        if(!pImageFileBuf)
        {
            strErrMsg += "In isProcessRunningByPid(), pImageFileBuf can not be zero when bGetImageFile=true!\n";
            return false;
        }
        if(puiBufSize == 0 || *puiBufSize == 0)
        {
            strErrMsg += "In isProcessRunningByPid(), puiBufSize or *puiBufSize can not be zero when bGetImageFile=true!\n";
            return false;
        }
    }

    bool bRnt = false;
#ifdef Q_OS_WIN     //windows platform
    DWORD dwPids[1000] = {0};   //save pids
    DWORD dwPidCnt = 1000;
    DWORD dwNeedLen = 0;
    bool bOk=::EnumProcesses( dwPids, dwPidCnt, &dwNeedLen);
    if(!bOk)
    {
        strErrMsg += QString("In isProcessRunningByPid(), EnumProcesses() fail! GetLastError() return %1\n").arg(::GetLastError());
        return false;
    }
    for(int i=0; i<(int)qMin(dwPidCnt,dwNeedLen); i++)
    {
        if(dwPids[i] != lPid) continue;

        if(!bGetImageFile)
        {
            bRnt = true;
            break;
        }
        HANDLE hProc = ::OpenProcess(PROCESS_QUERY_INFORMATION|PROCESS_VM_READ , false, dwPids[i]);
        if(!hProc)
        {
            strErrMsg += QString("In isProcessRunningByPid(), OpenProcess() fail! GetLastError() return %1\n").arg(::GetLastError());
            return false;
        }
        DWORD dwPathLen = ::GetModuleFileNameEx(hProc, 0, pImageFileBuf, *puiBufSize);
        ::CloseHandle(hProc);
        if(0 == dwPathLen)
        {
            strErrMsg += QString("In isProcessRunningByPid(), GetModuleFileNameEx() fail! GetLastError() return %1\n").arg(::GetLastError());
            return false;
        }
        *puiBufSize = dwPathLen;
        bRnt = true;
        break;
    }
#else   //linux platform
    QDir dirProcs("/proc");
    char acProcFile[1024] = {0};
    QStringList lstProcInfo = dirProcs.entryList(QDir::Dirs|QDir::NoDot|QDir::NoDotDot, QDir::Name);
    for(int i=0; i<lstProcInfo.length(); i++)
    {
        QString strDir = lstProcInfo.at(i);
        long lPid = strDir.mid(strDir.lastIndexOf("/")+1).toLong();
        if(lPid <= 0) continue;
        if(lPid != lPid) continue;
        bRnt = true;
        if(!bGetImageFile) break;
        memset(pImageFileBuf, 0, *puiBufSize);
        *puiBufSize = readlink((strDir+"/exe").toUtf8().constData(), pImageFileBuf, *puiBufSize-1);
        break;
    }
#endif
    return bRnt;
}

/*==========================================
//check if the process is running by executable filename
//
//strFilename: executable file, full or relative path(seperated by '/' or '\'), can contain ../, ./
//strErrMsg: if error occurs, not empty, else is empty
//lstPid: the process pids
//bGetAllPids: get all the pid? or just get the first one? the default is false
//
//author: moyannie
//date: 2011/06/22
//modified:
===========================================*/
bool SystemEx::isProcessRunningByFilename(QString strFilename, QString &strErrMsg,
                                          QList<qint64> &lstPid, bool bGetAllPids/*=false*/)
{
    bool bRnt = false;
    strErrMsg = "";

    QString strFullPathName = QDir(strFilename).canonicalPath().toLower();
    if (strFullPathName.isEmpty())    //if filename does not exist,return
        return false;

#ifdef Q_OS_WIN     //windows platform
    DWORD dwPids[1000] = {0};   //save pids
    DWORD dwPidCnt = 1000;
    DWORD dwNeedLen = 0;
    WCHAR szFilePath[1024];     //save imagefile path of the specified pid
    bool bOk=::EnumProcesses(dwPids, dwPidCnt, &dwNeedLen);
    if(!bOk)
    {
        strErrMsg += QString("In isProcessRunningByFilename(), EnumProcesses() fail! GetLastError() return %1\n").arg(::GetLastError());
        return false;
    }
    for(int i=0; i<(int)qMin(dwPidCnt,dwNeedLen); i++)
    {
        if(dwPids[i] <= 0) continue;
        HANDLE hProc = ::OpenProcess(PROCESS_QUERY_INFORMATION|PROCESS_VM_READ , false, dwPids[i]);
        if(!hProc) {/*strErrMsg+=QString::number(dwPids[i])+"\t"; */continue;}
        memset(szFilePath, 0, sizeof(szFilePath));
        DWORD dwPathLen = ::GetModuleFileNameEx(hProc, 0, szFilePath, sizeof(szFilePath));
        ::CloseHandle(hProc);
        if(0 == dwPathLen) continue;

        QString strPathName = QString::fromStdWString(szFilePath);
        if (strPathName.startsWith("\\")) // if the path contain systemEnvironment
        {
            //try to get the systemEnvironment
            int nFind = strPathName.indexOf("\\", 1);
            if (nFind > 0)
            {
                QString strEnvirenment = strPathName.mid(1, nFind - 1);
                QString strEndFile = strPathName.right(strPathName.length() - nFind);

                QProcessEnvironment env = QProcessEnvironment::systemEnvironment();
                QString strPrePath = env.value(strEnvirenment);

                strPathName = strPrePath + strEndFile;  //make the full path
            }
        }

        QString strFullPathNameEx = QDir(strPathName).canonicalPath().toLower();    //check if the file is exist.

        if(strFullPathNameEx == strFullPathName)    //found the process
        {
            bRnt = true;
            lstPid.append(dwPids[i]);
            if(!bGetAllPids) break;
        }
    }
#else   //linux platform
    QDir dirProcs("/proc");
    char acProcFile[1024] = {0};
    QStringList lstProcInfo = dirProcs.entryList(QDir::Dirs|QDir::NoDot|QDir::NoDotDot, QDir::Name);
    for(int i=0; i<lstProcInfo.length(); i++)
    {
        QString strDir = lstProcInfo.at(i);
        long lPid = strDir.mid(strDir.lastIndexOf("/")+1).toLong();
        if(lPid <= 0) continue;
        memset(acProcFile, 0, sizeof(acProcFile));
        readlink((strDir+"/exe").toUtf8().constData(), acProcFile, sizeof(acProcFile));
        if(QDir(QString(acProcFile)).canonicalPath().toLower() == QDir(strFilename).canonicalPath().toLower())
        {
            bRnt = true;
            lstPid.append(lPid);
            if(!bGetAllPids) break;
        }
    }
#endif
    return bRnt;
}

//kill process by pid
bool SystemEx::killProcessByPid(qint64 i64Pid)
{
    bool bOk = false;
#ifdef Q_OS_WIN
    QProcess proc;
    QString strCmd = QString("taskkill.exe /F /PID %1").arg(i64Pid);
    proc.start(strCmd);
    bOk = proc.waitForFinished(10*1000);
    proc.close();
#else
    char buf[100]={0};
    sprintf(buf, "kill -9 %ld", (long)i64Pid);
    bOk = (0 == system(buf));
#endif
    return bOk;
}

//kill Process By Filename
//bKillAll=true: kill all the process with the same imagefile, false: just kill the first one
bool SystemEx::killProcessByFilename(const QString &strFilename, QString &strErrMsg, bool bKillAll/*=true*/)
{
    strErrMsg = "";
    QString strErr; QList<qint64> lstPid;
    bool bRun = isProcessRunningByFilename(strFilename, strErr, lstPid, bKillAll);
    if(strErr.isEmpty())
    {
        bool bKillOk = true;
        if(bRun)
        {
            foreach(qint64 i64Pid, lstPid)
            {
                if(!killProcessByPid(i64Pid)) bKillOk = false;
            }
        }
        return bKillOk;
    }
    else
    {
        strErrMsg = strErr;
        return false;
    }
}

/****************************************************
Description: this function is called by killProcessByAppName()
             to find all process in os;
parameter: * std::string strAppName
             Process Name;
           * QString &strErrMsg;
           * QList<qint64> &lstPid;
             process ID
return value: bool
           if return true mean the process is found;
           if return false mean the process is not
           found;
author: liuwei
Date: 2011-11-29
****************************************************/
bool SystemEx::isProcessRunningByAppName(QString strAppName, QString &strErrMsg,
                                         QList<qint64> &lstPid, bool bGetAllPids/*=false*/)
{
    bool bRnt = false;
    strErrMsg = "";
    QString strName = strAppName;
#ifdef Q_OS_WIN     //windows platform
    DWORD dwPids[1000] = {0};   //save pids
    DWORD dwPidCnt = 1000;
    DWORD dwNeedLen = 0;
    WCHAR szFilePath[1024];     //save imagefile path of the specified pid
    bool bOk=::EnumProcesses(dwPids, dwPidCnt, &dwNeedLen);

    if(!bOk)
    {
        strErrMsg += QString("In isProcessRunningByFilename(), EnumProcesses() fail! GetLastError() return %1\n").arg(::GetLastError());
        return false;
    }
    for(int i=0; i<(int)qMin(dwPidCnt,dwNeedLen); i++)
    {
        if(dwPids[i] <= 0)
            continue;
        HANDLE hProc = ::OpenProcess(PROCESS_QUERY_INFORMATION|PROCESS_VM_READ , false, dwPids[i]);
        if(!hProc) {/*strErrMsg+=QString::number(dwPids[i])+"\t"; */continue;}
        memset(szFilePath, 0, sizeof(szFilePath));
        DWORD dwPathLen = ::GetModuleFileNameEx(hProc, 0, szFilePath, sizeof(szFilePath));
        ::CloseHandle(hProc);
        if(0 == dwPathLen)
            continue;
        std::wstring wstr = szFilePath;
        std::string strMbs( wstr.begin(),wstr.end());
        QString strCurrAppPath = strMbs.c_str();
        strCurrAppPath.toWCharArray( szFilePath);
        bool bRes = strCurrAppPath.contains( strName, Qt::CaseInsensitive);
        if( bRes == true)
        {
            bRnt = true;
            lstPid.append(dwPids[i]);
            if(!bGetAllPids)
                break;
        }
    }
#else   //linux platform
    QDir dirProcs("/proc");
    char acProcFile[1024] = {0};
    QStringList lstProcInfo = dirProcs.entryList(QDir::Dirs|QDir::NoDot|QDir::NoDotDot, QDir::Name);
    for(int i=0; i<lstProcInfo.length(); i++)
    {
        QString strDir = lstProcInfo.at(i);
        long lPid = strDir.mid(strDir.lastIndexOf("/")+1).toLong();
        if(lPid <= 0) continue;
        memset(acProcFile, 0, sizeof(acProcFile));
        readlink((strDir+"/exe").toUtf8().constData(), acProcFile, sizeof(acProcFile));
        if(QDir(QString(acProcFile)).canonicalPath().toLower() == QDir(strAppName).canonicalPath().toLower())
        {
            bRnt = true;
            lstPid.append(lPid);
            if(!bGetAllPids) break;
        }
    }
#endif
    return bRnt;
}

/****************************************************
Description: this function is used to kill a process
            by its name;
parameter: * const QString &strAppName;
             Process Name
           * QString &strErrMsg;
           * bool bKillAll;
return value: bool
           if return true mean the process is killed;
           if return false mean the process is not
           found, or kill process fault;
author: liuwei
Date: 2011-11-29
****************************************************/
bool SystemEx::killProcessByAppName(const QString &strAppName, QString &strErrMsg, bool bKillAll/*=true*/)
{
    strErrMsg = "";
    QString strErr; QList<qint64> lstPid;
    bool bRun = isProcessRunningByAppName(strAppName, strErr, lstPid, bKillAll);
    if(strErr.isEmpty())
    {
        bool bKillOk = true;
        if(bRun)
        {
            foreach(qint64 i64Pid, lstPid)
            {
                if(!killProcessByPid(i64Pid)) bKillOk = false;
            }
        }
        return bKillOk;
    }
    else
    {
        strErrMsg = strErr;
        return false;
    }
}

/*==========================================
//is one instance of the app had running before?
//
//strMtxName: the mutex name(only in windows)
//strAppFile: the app file(only in linux)
//
//author: moyannie
//date: 2011/07/19
//modified:
===========================================*/
bool SystemEx::isAppInstanceRunning(QString strMtxName, QString strAppFile)
{
#ifdef Q_OS_WIN
    Q_UNUSED(strAppFile)
    CreateMutex(NULL, false, QString("Global\\%1").arg(strMtxName).toStdWString().data());
    if(ERROR_ALREADY_EXISTS == GetLastError()) return true;
#else
    Q_UNUSED(strMtxName)
    QDir dirProcs("/proc");
    dirProcs.setFilter(QDir::Dirs);
    QStringList lstProcs = dirProcs.entryList();
    long lPid = 0; bool bOk = false; char buf[1024] = {0};
    int iRunningTimes = 0;
    for(int i=0; i<lstProcs.length(); i++)
    {
        if((lPid=lstProcs.at(i).toLong(&bOk)) && bOk)
        {
            memset(buf, 0, sizeof(buf));
            readlink(QString("/proc/%1/exe").arg(lstProcs.at(i)).toUtf8().constData(), buf, sizeof(buf));
            if(QString(buf) == QDir(strAppFile).canonicalPath())
            {
                if(++iRunningTimes > 1) return true;   //printf("the app have startup\n");
            }
        }
    }
#endif
    return false;
}

quint64 SystemEx::getDiskFreeSpace(const QString &driver)
{
    QDir dir(driver);
    //driver.endsWith(":")防止参数是c:会变成死循环
    while(!dir.isRoot() && dir.exists() && !driver.endsWith(":"))
    {
        dir.cdUp();
    }

    QStorageInfo storage(dir.path());
    if (storage.isValid() && storage.isReady()) {
        return storage.bytesFree();
    } else {
        return 0;
    }
    //#ifdef Q_OS_WIN
    //    LPCWSTR lpcwstrDriver=(LPCWSTR)driver.utf16();
    //    ULARGE_INTEGER liFreeBytesAvailable, liTotalBytes, liTotalFreeBytes;
    //    if( !GetDiskFreeSpaceEx( lpcwstrDriver, &liFreeBytesAvailable, &liTotalBytes, &liTotalFreeBytes) )
    //    {
    //        qDebug() << "ERROR: Call to GetDiskFreeSpaceEx() failed.";
    //        return 0;
    //    }
    //    return (quint64) liTotalFreeBytes.QuadPart;
    //#else
    //#endif
    return 0;
}

quint64 SystemEx::getDiskSpace(const QString &driver)
{
    QDir dir(driver);
    //driver.endsWith(":")防止参数是c:会变成死循环
    while(!dir.isRoot() && dir.exists() && !driver.endsWith(":"))
    {
        dir.cdUp();
    }

    QStorageInfo storage(dir.path());
    if (storage.isValid() && storage.isReady()) {
        return storage.bytesTotal();
    } else {
        return 0;
    }

    // 不是跨平台的代码，暂时不用
    //#ifdef Q_OS_WIN
    //    LPCWSTR lpcwstrDriver=(LPCWSTR)driver.utf16();
    //    ULARGE_INTEGER liFreeBytesAvailable, liTotalBytes, liTotalFreeBytes;
    //    if( !GetDiskFreeSpaceEx( lpcwstrDriver, &liFreeBytesAvailable, &liTotalBytes, &liTotalFreeBytes) )
    //    {
    //        qDebug() << "ERROR: Call to GetDiskFreeSpaceEx() failed.";
    //        return 0;
    //    }
    //    return (quint64) liTotalBytes.QuadPart;
    //#else
    //#endif
    return 0;
}
