#include "fileex.h"

#if defined(Q_OS_WIN)
#include <windows.h>
#endif

FileEx::FileEx()
{

}

FileEx::~FileEx()
{

}

bool FileEx::removeFile(const QString &strFileName)
{
    QDir dir(strFileName);
    return dir.remove(strFileName);
}

bool FileEx::witeFile(const QString &strFileName, const QByteArray &data,
                      const QIODevice::OpenModeFlag &mode)
{
    if (!strFileName.isEmpty())
    {
        QFileInfo fi(strFileName);
        QFile f(strFileName);
        QDir dir(fi.absoluteDir());
        if (!dir.exists())
        {
            dir.mkpath(fi.absolutePath());
        }
        if (dir.exists() && f.open(mode))
        {
            f.write(data);
            f.close();

            return true;
        }
    }

    return false;
}

QByteArray FileEx::readFile(const QString &strFileName)
{
    QByteArray data;
    QFile f(strFileName);

    if (f.open(QIODevice::ReadOnly))
    {
        data = f.readAll();
        f.close();
    }

    return data;
}

QString FileEx::fileSuffix(const QString &strFile)
{
    if (strFile.isEmpty() || QFile::exists(strFile))
    {
        return "";
    }

    QFileInfo info(strFile);
    return info.suffix();
}

//从目录及子目录中检索出所有文件名
QStringList FileEx::allFiles(const QString &strDir, const QStringList &nameFilters,
                             bool bFullPath)
{
    QStringList ret;
    // 这个函数可以执行任何任务，
    // 这里只是简单地输出各个文件（夹）的名字
    QDir dir(strDir);
    QStringList list = dir.entryList(QDir::Dirs, QDir::Name);
    for (QStringList::Iterator it = list.begin(); it != list.end(); it++)
    {
        if ("." != *it && ".." != *it)
        {
            ret.append(allFiles(strDir + QDir::separator() + *it, nameFilters, bFullPath));
        }
    }
    list = dir.entryList(nameFilters, QDir::Files, QDir::Name);
//    list = dir.entryList(nameFilters, QDir::Files, QDir::Name);
    for (QStringList::Iterator it = list.begin(); it != list.end(); it++)
    {
        QString add = *it;
        if(bFullPath)
        {
            add = strDir + QDir::separator() + add;
        }
        ret.append(add);
    }

    return ret;
}

QString FileEx::getHash(const QString &strFilename, const QCryptographicHash::Algorithm &method)
{
    if(!QFileInfo::exists(strFilename))
    {
        return "";
    }

    QFile file(strFilename);
    if(!file.open(QIODevice::ReadOnly))
    {
        return "";
    }

    QByteArray byHash;
    if (false)
    {
        //大文件时候会线程阻塞卡住,有UI的地方废弃不用
//        byHash = QCryptographicHash::hash(file.readAll(), method);
        QCryptographicHash hs(QCryptographicHash::Md5);
        hs.addData(&file);
        byHash = hs.result();
    } else {
        //有个弊端：文件太大了会很耗时阻塞执行的线程
        QCryptographicHash hs(QCryptographicHash::Md5);
        QByteArray buffer;
        while (!(buffer = file.read(10 * 1024 * 1024)).isEmpty())
        {
            hs.addData(buffer);
            //加上不会造成主界面卡死
            QCoreApplication::processEvents();
        }
        byHash = hs.result();
    }
    file.close();

    return QString(byHash.toHex().data());
}

QString FileEx::fileSize2String(const qint64 &i64FileSize)
{
    qint32 iG = i64FileSize / 1024 / 1024 / 1024;
    if ( iG > 0)
    {
        qint32 iM = i64FileSize / 1024 / 1024 % 1024 / 10;

        return QString::number(iG) + "." + QString::number(iM) + "GB";
    }

    qint32 iM = i64FileSize / 1024 / 1024;
    if (iM > 0)
    {
        qint32 iK = i64FileSize / 1024 % 1024 / 10;

        return QString::number(iM) + "." + QString::number(iK) + "MB";
    }

    qint32 iK = i64FileSize / 1024;
    if (iK > 0)
    {
        qint32 iB = i64FileSize % 1024 / 10;

        return QString::number(iK) + "." + QString::number(iB) + "KB";
    }

    return QString::number(i64FileSize) + "b";
}

//QString FileEx::fileVersion(const QString & exeFile)
//{
//    QString ret;

//#if defined(Q_OS_WIN)
//    int size = GetFileVersionInfoSize(exeFile.toStdWString().c_str(), NULL);
//    if (size > 0)
//    {
//        char* data = new char[size +1];
//        if (GetFileVersionInfo(exeFile.toStdWString().c_str(), 0, size, data))
//        {
//            VS_FIXEDFILEINFO* fileInfo;
//            unsigned int      fileInfoSize = 0;
//            if (VerQueryValue(data, L"\\", (void**)&fileInfo, &fileInfoSize))
//            {
//                int vMajor  = HIWORD(fileInfo->dwFileVersionMS);
//                int vMinor  = LOWORD(fileInfo->dwFileVersionMS);
//                int Release = HIWORD(fileInfo->dwFileVersionLS);
//                int vBuild  = LOWORD(fileInfo->dwFileVersionLS);
//                ret.append(QString::number(vMajor)).append(".")
//                        .append(QString::number(vMinor)).append(".")
//                        .append(QString::number(Release)).append(".")
//                        .append(QString::number(vBuild));
//            }
//        }
//        delete [] data;
//    }
//#else
//    Q_UNUSED(exeFile)
//#endif
//    return ret;
//}

