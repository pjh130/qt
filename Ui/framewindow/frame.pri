#useage:
#include($$PWD/xxx.pri)

greaterThan(QT_MAJOR_VERSION, 4){
    QT += widgets
}else{

}

#加入路径
FRAME_LIBRARY_LOCATION = $$PWD
INCLUDEPATH += $$FRAME_LIBRARY_LOCATION
DEPENDPATH += $$FRAME_LIBRARY_LOCATION

HEADERS += \
    $$PWD/noframeDialog.h \
    $$PWD/windowframe.h

SOURCES += \
    $$PWD/noframeDialog.cpp \
    $$PWD/windowframe.cpp

win32 {
HEADERS += \
    $$PWD/blurWindow.h \
    $$PWD/qtwin.h

SOURCES += \
    $$PWD/blurWindow.cpp \
    $$PWD/qtwin.cpp
}

RESOURCES += \
    $$PWD/res.qrc
