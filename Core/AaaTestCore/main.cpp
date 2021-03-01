#include "mainwindow.h"
#include <QApplication>
#include "textcodecex.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    //设置字符集
    TextCodecEx::setCodecForLocale();

    MainWindow w;
    w.show();

    return a.exec();
}
