#useage:
#include($$PWD/xxx.pri)

#加入路径
STRING_LIBRARY_LOCATION = $$PWD
INCLUDEPATH += $$STRING_LIBRARY_LOCATION
DEPENDPATH += $$STRING_LIBRARY_LOCATION

#tchinese这个类中需要
win32 {
    LIBS += -luser32
}

win32 {
HEADERS += \
    $$PWD/msime.h
}

HEADERS += \
    $$PWD/stringex.h \
    $$PWD/tcchinese.h

SOURCES += \
    $$PWD/stringex.cpp \
    $$PWD/tcchinese.cpp
