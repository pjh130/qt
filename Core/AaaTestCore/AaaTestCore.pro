#-------------------------------------------------
#
# Project created by QtCreator 2021-02-26T13:40:18
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4){
    QT += widgets
    message("test ...")
}else{
    message("pla,pla,pla ....")
}

include(D:\Code\Go\src\github.com\pjh130\qt\Core\core.pri)
include(D:\Code\Go\src\github.com\pjh130\qt\Ui\ui.pri)

TARGET = AaaTestCore
TEMPLATE = app

DEFINES += QT_MESSAGELOGCONTEXT

SOURCES += main.cpp\
        mainwindow.cpp

HEADERS  += mainwindow.h

FORMS    += mainwindow.ui
