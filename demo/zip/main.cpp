#include <QCoreApplication>
#include <QStringList>
#include <QDir>
#include <QDebug>
#include "JlCompress.h"

/*
用QuaZip中的JlCompress类来压缩和解压缩文件
静态方法压缩文件
static bool compressDir(QString fileCompressed, QString dir=QString(), bool recursive = true)
第一个参数fileCompressed表示压缩后的文件
第二个参数dir表示待压缩的目录
第三个参数recursive表示是否递归
解压缩用静态方法：extractDir
static QStringList extractDir(QString fileCompressed, QString dir=QString())
第一个参数fileCompressed表示待解压缩的文件
第二个参数表示解压缩存放的目录
*/

QString g_absolutePath;
QString g_testPath;

QString g_compressedPath;
QString g_compressedPathNew;

bool compressDir()
{
    bool bOk;
    g_compressedPath = g_testPath + "\\compressed.zip";
    QString strDir = g_testPath + "\\dir";
    bOk = JlCompress::compressDir(g_compressedPath, strDir);
    return bOk;
}

QStringList extractDir()
{
    g_compressedPathNew = g_testPath + "\\new";
    QStringList lst = JlCompress::extractDir(g_compressedPath, g_compressedPathNew);
    return lst;
}

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    QDir fdir = QDir(QDir(a.applicationDirPath()));
    QDir fdirTest;

    g_absolutePath = fdir.absolutePath();
    QDir::setCurrent(g_absolutePath);
    g_testPath = g_absolutePath + "\\test";

    qDebug()<<"the fdir absolutePath"<<g_absolutePath;
    qDebug()<<"the fdir testPath"<<g_testPath;

    if (fdirTest.exists(g_testPath))
    {
        qDebug()<<"Dir is already existed!";
    } else {
        bool bOk = fdirTest.mkdir(g_testPath);
        qDebug()<<"Create Dir: "<<bOk;
    }

    //测试
     qDebug()<<"compressDir Dir: "<<compressDir();
     qDebug()<<"extractDir Dir: "<<extractDir();

     //删除测试文件
     QDir dir1(g_compressedPath);
     qDebug()<<"remove Dir: "<<dir1.absolutePath()<<" "<<dir1.removeRecursively();
     QDir dir2(g_compressedPathNew);
     qDebug()<<"remove Dir: "<<dir2.absolutePath()<<" "<<dir2.removeRecursively();

    return a.exec();
}
