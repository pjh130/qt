#-------------------------------------------------
#
# Project created by QtCreator 2015-06-18T22:44:30
#
#-------------------------------------------------

QT       -= gui

TARGET = lib
TEMPLATE = lib

DEFINES += LIB_LIBRARY

SOURCES += lib.cpp

HEADERS += lib.h\
        lib_global.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}
