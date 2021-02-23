1、简介
QuaZIP是使用Qt，C++对ZLIB进行简单封装的用于压缩ZIP以及解压缩ZIP的开源库。如果你的Qt项目当中用到了压缩以及解压缩ZIP的话你可以考虑选择使用它。
官方主页：http://quazip.sourceforge.net/
souceforge下载地址：http://sourceforge.net/projects/quazip/


2、编译
QuaZip是基于Zlib库的，编译前要导入zlib的头文件，编译后会生成quazip.lib和quazip.dll文件（用的是vs）
如果用Qt来编译，直接编译会报错，需要添加zlib.h的包含目录，在quazip/quazip.pro文件中添加INCLUDEPATH += "E:\develop\Qt\5.4.1\5.4\msvc2013_64_opengl\include\QtZlib"
同时将quazip.pro文件中的SUBDIRS = quazip qztest注释，换成SUBDIRS = quazip，选择“重新构建”会生成libquazipd.a和quazipd.dll

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