QT += core network
QT -= gui

CONFIG += c++11

TARGET = HttpJsonServer
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp \
    qasyntcpserver.cpp \
    qhttpserver.cpp \
    qasynhttpsocket.cpp

HEADERS += \
    qasyntcpserver.h \
    qhttpserver.h \
    qasynhttpsocket.h
