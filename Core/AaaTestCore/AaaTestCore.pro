#-------------------------------------------------
#
# Project created by QtCreator 2021-02-26T13:40:18
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

include(D:\Code\Go\src\github.com\pjh130\qt\Core\email\email.pri)
include(D:\Code\Go\src\github.com\pjh130\qt\Core\log_v1\log_v1.pri)
include(D:\Code\Go\src\github.com\pjh130\qt\Core\network_v1\network_v1.pri)
include(D:\Code\Go\src\github.com\pjh130\qt\Core\ThreadHandle\threadhandle.pri)
include(D:\Code\Go\src\github.com\pjh130\qt\Core\excel\excel.pri)
include(D:\Code\Go\src\github.com\pjh130\qt\Core\qzip\qzip.pri)
include(D:\Code\Go\src\github.com\pjh130\qt\Core\qtsql\qtsql.pri)
include(D:\Code\Go\src\github.com\pjh130\qt\Core\file\file.pri)
include(D:\Code\Go\src\github.com\pjh130\qt\Core\time\time.pri)
include(D:\Code\Go\src\github.com\pjh130\qt\Core\image\image.pri)
include(D:\Code\Go\src\github.com\pjh130\qt\Core\string\string.pri)
include(D:\Code\Qt\toStudy\tianchi\src\lib.pri)

TARGET = AaaTestCore
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp

HEADERS  += mainwindow.h

FORMS    += mainwindow.ui
