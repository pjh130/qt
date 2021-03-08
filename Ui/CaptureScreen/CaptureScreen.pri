#useage:
#include($$PWD/xxx.pri)

QT       += core gui widgets

#加入路径
CAPTURE_LIBRARY_LOCATION = $$PWD
INCLUDEPATH += $$CAPTURE_LIBRARY_LOCATION
DEPENDPATH += $$CAPTURE_LIBRARY_LOCATION

#include(qxtglobalshortcut/qxtglobalshortcut.pri)

SOURCES += \
    $$PWD/capturewidget.cpp \
    $$PWD/capselector.cpp \
    $$PWD/toolbarcommon.cpp \
    $$PWD/texttoolbar.cpp \
    $$PWD/recttoolbar.cpp

HEADERS += \
    $$PWD/capturewidget.h \
    $$PWD/capselector.h \
    $$PWD/globalDataType.h \
    $$PWD/toolbarcommon.h \
    $$PWD/texttoolbar.h \
    $$PWD/recttoolbar.h

FORMS += \
    $$PWD/toolbarcommon.ui \
    $$PWD/texttoolbar.ui \
    $$PWD/recttoolbar.ui

RESOURCES += \
    $$PWD/res/resources.qrc





