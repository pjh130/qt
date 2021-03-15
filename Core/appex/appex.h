#ifndef APPEX_H
#define APPEX_H

#include <QObject>
#include <QFile>
#include <QDir>
#include <QFileInfo>
#include <QApplication>
#include <QDebug>

class AppEx : public QObject
{
    Q_OBJECT
public:
    explicit AppEx(QObject *parent = nullptr);
    ~AppEx();

    //生成一个自动打包的脚本,参数都为空的时候，默认生成当前程序的打包脚本
    static bool deployQt(const QString &strAppPath = "", const QString &strWindeployqt = "");

protected:

private:

public slots:

signals:

private:

};

#endif // APPEX_H
