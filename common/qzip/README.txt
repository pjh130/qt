从quazip项目提取出来的头文件和库

使用说明:
static bool 	compressFile (QString fileCompressed, QString file)
 	Compress a single file.
static bool 	compressFiles (QString fileCompressed, QStringList files)
 	Compress a list of files.
static bool 	compressDir (QString fileCompressed, QString dir=QString(), bool recursive=true)
 	Compress a whole directory.
static bool 	compressDir (QString fileCompressed, QString dir, bool recursive, QDir::Filters filters)
 	Compress a whole directory.
static QString 	extractFile (QString fileCompressed, QString fileName, QString fileDest=QString())
 	Extract a single file.
static QStringList 	extractFiles (QString fileCompressed, QStringList files, QString dir=QString())
 	Extract a list of files.
static QStringList 	extractDir (QString fileCompressed, QString dir=QString())
 	Extract a whole archive.
static QStringList 	getFileList (QString fileCompressed)
 	Get the file list.
static QString 	extractFile (QIODevice *ioDevice, QString fileName, QString fileDest=QString())
 	Extract a single file.
static QStringList 	extractFiles (QIODevice *ioDevice, QStringList files, QString dir=QString())
 	Extract a list of files.
static QStringList 	extractDir (QIODevice *ioDevice, QString dir=QString())
 	Extract a whole archive.
static QStringList 	getFileList (QIODevice *ioDevice)
 	Get the file list.