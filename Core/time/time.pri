#useage:
    ##include <windows.h>
    #// 在后台线程中使用QAxObject必须先初始化
    #CoInitializeEx(NULL, COINIT_MULTITHREADED);
#include($$PWD/xxx.pri)

#加入路径
TIME_LIBRARY_LOCATION = $$PWD
INCLUDEPATH += $$TIME_LIBRARY_LOCATION
DEPENDPATH += $$TIME_LIBRARY_LOCATION

HEADERS += \
    $$PWD/timeex.h

SOURCES += \
    $$PWD/timeex.cpp

