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

bool FileEx::witeFile(QString strFileName, QByteArray data,
              QIODevice::OpenModeFlag mode)
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

QByteArray FileEx::readFile(QString strFileName)
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

//从目录及子目录中检索出所有文件名
QStringList FileEx::allFiles(const QString & strDir)
{
    QStringList ret;
    // 这个函数可以执行任何任务，
    // 这里只是简单地输出各个文件（夹）的名字
    QDir dir(strDir);
    QStringList
    list = dir.entryList(QDir::Dirs, QDir::Name);
    for (QStringList::Iterator it = list.begin(); it != list.end(); it++)
    {
        if ("." != *it && ".." != *it)
        {
            ret.append(allFiles(strDir + QDir::separator() + *it));
        }
    }
    list = dir.entryList(QDir::Files, QDir::Name);
    for (QStringList::Iterator it = list.begin(); it != list.end(); it++)
    {
        ret.append(*it);
    }

    return ret;
}

QString FileEx::getHash(const QString &strFilename, QCryptographicHash::Algorithm method)
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

    QByteArray byHash = QCryptographicHash::hash(file.readAll(), method);

    file.close();

    return QString(byHash.toHex().data());
}

QString FileEx::fileSize2String(qint64 i64FileSize)
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

