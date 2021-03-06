#include "direx.h"

DirEx::DirEx()
{

}

DirEx::~DirEx()
{

}

QStringList DirEx::findFiles(const QString &path,
        const QStringList &nameFilters)
{
    QStringList files;
    if ((!path.isEmpty()) && (QFileInfo(path).exists()))
    {
        doDirTree(path, path, nameFilters, false, files, true);
    }
    return files;
}

int DirEx::copyDirs(const QString &fromPath, const QString &toPath,
                               const QStringList &nameFilters, bool overWrite)
{
    resetCopyFileCount();

    if ((!fromPath.isEmpty()) && (QFileInfo(fromPath).exists()))
    {
        QStringList files;
        doDirTree(fromPath, toPath, nameFilters, overWrite, files, false);
    }
    return m_copyFileCount;
}

int DirEx::copyFiles(const QStringList &files, const QString &toPath,
        bool overWrite)
{
    int size = files.size();
    int count = 0;
    QString to_path(formatPath(toPath));
    QDir to_dir;
    QFile old_file;
    QFile new_file;
    QFileInfo old_file_info;
    QFileInfo new_file_info;

    for (int i = 0; i < size; i++)
    {
        old_file.setFileName(files[i]);
        old_file_info.setFile(old_file);
        new_file.setFileName(to_path + QDir::separator()
                + old_file_info.fileName());
        new_file_info.setFile(new_file);
        to_dir.setPath(new_file.fileName());
        to_dir.mkpath(new_file_info.path());

        if ((overWrite) || (!new_file.exists()))
        {
            old_file.copy(new_file.fileName());
            m_copyFileCount++;
            count++;
//            emit currentFile(m_copyFileCount, files[i]);
        }
    }
    return count;
}

void DirEx::resetCopyFileCount()
{
    m_copyFileCount = 0;
}

void DirEx::doDirTree(const QString &fromPath, const QString &toPath,
                          const QStringList &nameFilters, bool overWrite,
                          QStringList &findFiles, bool isFind)
{
    QQueue<QString> from_all_dirs;
    QQueue<QString> to_all_dirs;
    QDir find_in_dir;
    QStringList file_list;
    QStringList dir_list;
    QString current_from_path;
    QString current_to_path;

    from_all_dirs.push_back(fromPath);
    to_all_dirs.push_back(toPath);

    while (from_all_dirs.size() > 0)
    {
        current_from_path = from_all_dirs.head();
        current_to_path = to_all_dirs.head();
        find_in_dir.setPath(current_from_path);
        file_list = find_in_dir.entryList(nameFilters, QDir::Files);

        for (int i = 0; i < file_list.size(); i++)
        {
            file_list[i] = formatPath(current_from_path) + file_list[i];
        }

        if (isFind)
        {
            findFiles += file_list;
        }
        else
        {
            copyFiles(file_list, current_to_path, overWrite);
        }
        dir_list = find_in_dir.entryList(QDir::AllDirs | QDir::NoDotAndDotDot);

        for (int i = 0; i < dir_list.size(); i++)
        {
            from_all_dirs += formatPath(current_from_path) + dir_list[i];
            to_all_dirs += formatPath(current_to_path) + dir_list[i];
        }
        from_all_dirs.pop_front();
        to_all_dirs.pop_front();
    }
}

QString DirEx::formatPath(const QString &path)
{
    QString new_path = path;
    QString last_char = path[path.size() - 1];

    if (last_char != "\\" && last_char != "/")
    {
        new_path += QDir::separator();
    }
    return new_path;
}

QString DirEx::toSameSeparator(const QString &strPath, const QString &strSeparator)
{
    QString strNew = strPath;
    strNew = strNew.replace("\\", strSeparator);
    strNew = strNew.replace("/", strSeparator);

    return strNew;
}

QStringList DirEx::removeWorkDir(const QString &workDir, const QStringList &filters)
{
    QStringList result;
    QDir dir(workDir);
    if (!dir.exists())
        return result;

    QFileInfoList dirs = dir.entryInfoList(QDir::Dirs | QDir::NoDotAndDotDot);

    foreach (QFileInfo d, dirs) {
        removeWorkDir(d.filePath(),filters);
    }

    QFileInfoList files = dir.entryInfoList(filters,QDir::Files);
    foreach (QFileInfo f, files) {
        bool b = QFile::remove(f.filePath());
        if (b) {
            result << f.fileName();
        }
    }
    return result;
}

bool DirEx::CopyDirectory(const QString &src, const QString &dest)
{
    QDir dir(src);
    foreach(QFileInfo info, dir.entryInfoList(QDir::Files)) {
        if (info.isFile() && !info.isSymLink()) {
            QFile in(info.filePath());
            if (!in.open(QFile::ReadOnly)) {
                return false;
            }
            QFile out(dest+"/"+info.fileName());
            if (!out.open(QFile::WriteOnly)) {
                return false;
            }
            out.write(in.readAll());
        }
    }
    return true;
}
