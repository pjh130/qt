QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

include(D:\Code\Go\src\github.com\pjh130\qt\Core\core.pri)
#include(D:\Code\Go\src\github.com\pjh130\qt\Ui\ui.pri)

VERSION = 1.0
QMAKE_TARGET_PRODUCT = "Clear"
QMAKE_TARGET_COMPANY = "panpan"
QMAKE_TARGET_COPYRIGHT = "Copyright (C) panpan <panpan@xxx.com>"
QMAKE_TARGET_DESCRIPTION = "Delete the files found"

UI_DIR      	=  temp/ui    #指定uic命令将.ui文件转化成ui_*.h文件的存放的目录
OBJECTS_DIR 	=  temp/obj   #指定目标文件(obj)的存放目录
MOC_DIR     	=  temp/moc   #指定moc命令将含Q_OBJECT的头文件转换成标准.h文件的存放目录
RCC_DIR     	=  temp/rcc   #指定rcc命令将.qrc文件转换成qrc_*.h文件的存放目录

SOURCES += \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    mainwindow.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
