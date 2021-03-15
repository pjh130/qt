#include "appex.h"

AppEx::AppEx(QObject *parent) : QObject(parent)
{

}

AppEx::~AppEx()
{

}

bool AppEx::deployQt(const QString &strAppPath, const QString &strWindeployqt)
{
    QString strName = "deploy.bat";
    QString strFile;
    QString strDeploy = "windeployqt.exe";
    QString strApp;
    //检查参数如果为空就给默认值
    if(strAppPath.isEmpty())
    {
        strFile = QApplication::applicationDirPath() + QDir::separator() + strName;
        strApp = QFileInfo(QApplication::applicationFilePath()).fileName();
    } else {
        if (!QFile::exists(strAppPath))
        {
            return false;
        } else {
            QFileInfo info(strAppPath);
            strFile = info.absolutePath() + QDir::separator() + strName;
            strApp = info.fileName();
        }
    }

    //检查参数如果为空就给默认值
    if (!strWindeployqt.isEmpty() && QFile::exists(strWindeployqt))
    {
        strDeploy = strWindeployqt;
    }

    QFile file(strFile);
    if (file.open(QIODevice::WriteOnly))
    {
        qDebug()<<"Deploy file: "<<strFile;
        QString strWrite = strDeploy + " " + strApp + "\r\npause";
        file.write(strWrite.toUtf8());
        file.close();
        return true;
    } else {
        qDebug()<<file.errorString();
    }
    return false;
}
