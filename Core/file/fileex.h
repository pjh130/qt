#ifndef FILEEX_H
#define FILEEX_H
#include <QtCore>
#include <QFile>
#include <QDir>
#include <QFileInfo>
#include <QHash>
#include <QCryptographicHash>
#include "direx.h"

class FileEx
{
public:
    FileEx();
    ~FileEx();
    static bool removeFile(const QString &strFileName);
    //把数据写到文件中
    static bool witeFile(const QString &strFileName, const QByteArray &data,
                         const QIODevice::OpenModeFlag &mode = QIODevice::Append);
    //从文件中读取数据
    static QByteArray readFile(const QString &strFileName);

    //从目录及子目录中检索出所有文件名
    static QStringList allFiles(const QString &strDir, const QStringList &nameFilters = QStringList(),
                                bool bFullPath = false);
    //文件后缀
    static QString fileSuffix(const QString &strFile);

    static QString getHash(const QString &strFilename,
                                   const QCryptographicHash::Algorithm &method = QCryptographicHash::Md5);
    static QString fileSize2String(const qint64 &i64FileSize);

    /// @brief 取执行文件的版本，仅支持 Windows
    /// @param [in] exeFile 包含版本信息的文件名(.exe, .dll等)
    /// @return 版本信息(xxx.xxx.xxx.xxx)
//    static QString fileVersion(const QString & exeFile);

};

#endif // FILEEX_H
