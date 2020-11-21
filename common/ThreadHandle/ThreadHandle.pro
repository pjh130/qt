#-------------------------------------------------
#
# Project created by QtCreator 2020-11-21T16:18:10
#
#-------------------------------------------------

QT       -= gui

TARGET = ThreadHandle
TEMPLATE = lib

DEFINES += THREADHANDLE_LIBRARY

SOURCES += threadhandle.cpp

HEADERS += threadhandle.h\
        threadhandle_global.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}
