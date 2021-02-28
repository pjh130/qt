#useage:
    ##include <windows.h>
    #// 在后台线程中使用QAxObject必须先初始化
    #CoInitializeEx(NULL, COINIT_MULTITHREADED);
#include($$PWD/xxx.pri)

#加入路径
FILE_LIBRARY_LOCATION = $$PWD
INCLUDEPATH += $$FILE_LIBRARY_LOCATION
DEPENDPATH += $$FILE_LIBRARY_LOCATION

HEADERS += \
    $$PWD/direx.h \
    $$PWD/fileex.h

SOURCES += \
    $$PWD/direx.cpp \
    $$PWD/fileex.cpp

