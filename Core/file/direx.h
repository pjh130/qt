#ifndef DIREX_H
#define DIREX_H
#include <QtCore>

/*
 * 【须知:】代码从天池代码共享库拷贝过来，作为个人代码积累用，非常感谢他们！
 * 天池共享源码库 版权所有 (C) 天池共享源码库开发组
*/
class DirEx
{
public:
    DirEx();
    ~DirEx();

    //转换成相同的分隔符
    static QString toSameSeparator(const QString &strPath, const QString &strSeparator = QDir::separator());
    //删除文件夹
    static QStringList removeWorkDir(const QString &workDir, const QStringList &filters);
    //拷贝文件夹(仅仅针对第一级目录)
    static bool CopyDirectory(const QString &src, const QString &dest);


    /// @brief 查找文件夹内所有的文件
    /// @param path 要查找的文件夹
    /// @param nameFilters 文件过滤
    /// @return 找到的文件列表
    QStringList findFiles(const QString &path,
                          const QStringList &nameFilters = QStringList());

    /// @brief 复制目录树下所有的文件到新文件夹
    /// @param fromPath 源文件夹
    /// @param toPath 目的文件夹
    /// @param nameFilters 文件过滤
    /// @param overWrite 是否覆盖
    /// @return 复制的文件数量
    int copyDirs(const QString &fromPath, const QString &toPath,
                 const QStringList &nameFilters = QStringList(),
                 bool overWrite = true);

    /// @brief 复制文件列表到新文件夹
    /// @param files 源文件列表
    /// @param toPath 目的文件夹
    /// @param overWrite 是否覆盖
    /// @return 复制的文件数量
    int copyFiles(const QStringList &files, const QString &toPath,
                  bool overWrite = true);

    /// @brief 重置m_copyFileCount为0
    void resetCopyFileCount();

    /// @brief 当前复制的文件的计数和文件名
    /// @param count 第几个文件
    /// @param name 源文件名
    void currentFile(int count, const QString &name);

private:
    int m_copyFileCount;
    void doDirTree(const QString &fromPath, const QString &toPath,
                   const QStringList &nameFilters, bool overWrite,
                   QStringList &findFiles, bool isFind);
    QString formatPath(const QString &path);
};

#endif // DIREX_H
