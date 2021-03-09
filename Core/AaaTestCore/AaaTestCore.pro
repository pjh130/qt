#-------------------------------------------------
#
# Project created by QtCreator 2021-02-26T13:40:18
#
#-------------------------------------------------

QT       += core gui

#VERSION = 1.0

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
        form_textedit.cpp \
        mainwindow.cpp

HEADERS  += mainwindow.h \
    form_textedit.h

FORMS    += mainwindow.ui \
    form_textedit.ui
