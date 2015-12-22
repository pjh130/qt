#-------------------------------------------------
#
# Project created by QtCreator 2011-12-30T10:45:19
#
#-------------------------------------------------

QT       += core gui

TARGET = shortcut
TEMPLATE = lib

INCLUDEPATH += $$PWD

include($$PWD/qxtglobalshortcut.pri)

DEFINES += QXTSHORTCUT_LIBRARY

SOURCES += QXTShortCut.cpp

HEADERS += QXTShortCut.h\
        QXTShortCut_global.h

unix:!symbian {
    maemo5 {
        target.path = /opt/usr/lib
    } else {
        target.path = /usr/local/lib
    }
    INSTALLS += target
}


CONFIG(release, debug|release) {
    DESTDIR=$$PWD/../../Mod/INCX/release

}
else:CONFIG(debug,debug|release) {
    DESTDIR=$$PWD/../../Mod/INCX/debug
    TARGET = $$member(TARGET, 0)d
}
