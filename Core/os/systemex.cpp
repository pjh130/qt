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
