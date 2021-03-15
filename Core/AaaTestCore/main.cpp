#include "mainwindow.h"
#include <QApplication>
#include "textcodecex.h"
#include <QHotkey>
#include "appex.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    //生成部署的脚本
    AppEx::deployQt();
//    AppEx::deployQt(QApplication::applicationFilePath());
//    AppEx::deployQt(QApplication::applicationFilePath(), "xxx");

    //设置字符集
    TextCodecEx::setCodecForLocale();

    auto hotkey = new QHotkey(QKeySequence("ctrl+alt+Q"), true, &a);//The hotkey will be automatically registered
        qDebug() << "Is Registered: " << hotkey->isRegistered();

        QObject::connect(hotkey, &QHotkey::activated, qApp, [&](){
            qDebug() << "Hotkey Activated - the application will quit now";
            qApp->quit();
        });

    MainWindow w;
    w.show();

    return a.exec();
}
