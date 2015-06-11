#-------------------------------------------------
#
# Project created by QtCreator 2015-06-11T13:25:13
#
#-------------------------------------------------

QT       += core

QT       -= gui

TARGET = factory3
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += main.cpp \
    AbstractFactory.cpp \
    AbstractProductA.cpp \
    AbstractProductB.cpp

HEADERS += \
    AbstractFactory.h \
    AbstractProductA.h \
    AbstractProductB.h
