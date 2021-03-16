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
#include(D:\Code\Qt\toStudy\tianchi\src\lib.pri)

TARGET = AaaTestCore
TEMPLATE = app

OBJECTS_DIR 	=  temp/obj   #指定目标文件(obj)的存放目录
MOC_DIR     	=  temp/moc   #指定moc命令将含Q_OBJECT的头文件转换成标准.h文件的存放目录
RCC_DIR     	=  temp/rcc   #指定rcc命令将.qrc文件转换成qrc_*.h文件的存放目录

DEFINES += QT_MESSAGELOGCONTEXT

SOURCES += main.cpp\
        form_textedit.cpp \
        mainwindow.cpp \
        mywidget.cpp

HEADERS  += mainwindow.h \
    form_textedit.h \
    mywidget.h

FORMS    += mainwindow.ui \
    form_textedit.ui

OTHER_FILES +=
