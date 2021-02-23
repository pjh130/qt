#-------------------------------------------------
#
# Project created by QtCreator 2021-02-22T17:27:09
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = myzip
TEMPLATE = app



win32 {
    # workaround for qdatetime.h macro bug
    DEFINES += NOMINMAX
}

include(D:\Code\Go\src\github.com\pjh130\qt\common\qzip\qzip.pri)

SOURCES += main.cpp\
        mainwindow.cpp

HEADERS  += mainwindow.h

FORMS    += mainwindow.ui
