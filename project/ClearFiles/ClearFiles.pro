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
