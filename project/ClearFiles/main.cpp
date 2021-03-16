#include "mainwindow.h"
#include "appex.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //生成一个打包脚本
    AppEx::deployScript();

    MainWindow w;
    w.show();

    return a.exec();
}
