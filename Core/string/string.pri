#useage:
    ##include <windows.h>
    #// 在后台线程中使用QAxObject必须先初始化
    #CoInitializeEx(NULL, COINIT_MULTITHREADED);
#include($$PWD/xxx.pri)

#加入路径
STRING_LIBRARY_LOCATION = $$PWD
INCLUDEPATH += $$STRING_LIBRARY_LOCATION
DEPENDPATH += $$STRING_LIBRARY_LOCATION

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
