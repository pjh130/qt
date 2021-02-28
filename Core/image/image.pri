#useage:
    ##include <windows.h>
    #// 在后台线程中使用QAxObject必须先初始化
    #CoInitializeEx(NULL, COINIT_MULTITHREADED);
#include($$PWD/xxx.pri)

#加入路径
IMAGE_LIBRARY_LOCATION = $$PWD
INCLUDEPATH += $$IMAGE_LIBRARY_LOCATION
DEPENDPATH += $$IMAGE_LIBRARY_LOCATION

HEADERS += \
    $$PWD/imageex.h

SOURCES += \
    $$PWD/imageex.cpp

