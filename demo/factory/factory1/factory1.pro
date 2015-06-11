#-------------------------------------------------
#
# Project created by QtCreator 2015-06-11T13:20:16
#
#-------------------------------------------------

QT       += core

QT       -= gui

TARGET = factory1
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += main.cpp \
    AbstractProduct.cpp \
    SimpleFactory.cpp

HEADERS += \
    AbstractProduct.h \
    SimpleFactory.h
