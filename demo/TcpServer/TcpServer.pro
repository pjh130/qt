#-------------------------------------------------
#
# Project created by QtCreator 2016-03-24T20:15:24
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = TcpServer
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    tcpthread.cpp \
    tcpserver.cpp

HEADERS  += mainwindow.h \
    tcpthread.h \
    tcpserver.h

FORMS    += mainwindow.ui
