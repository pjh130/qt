#include "mainwindow.h"
#include <QApplication>
#include "textcodecex.h"
#include <QHotkey>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

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
