#-------------------------------------------------
#
# Project created by QtCreator 2015-11-20T20:52:41
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = HttpTool
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    parameteritem.cpp

HEADERS  += mainwindow.h \
    parameteritem.h

FORMS    += mainwindow.ui \
    parameteritem.ui
