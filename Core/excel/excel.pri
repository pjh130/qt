#useage:
    ##include <windows.h>
    #// 在后台线程中使用QAxObject必须先初始化
    #CoInitializeEx(NULL, COINIT_MULTITHREADED);
#include($$PWD/xxx.pri)
#https://github.com/dbzhang800/QtXlsxWriter这个跟自己的没任何关系，可以去参考一下扩展补充

QT += axcontainer

HEADERS += \
        $$PWD/excelbase.h
SOURCES += \
        $$PWD/excelbase.cpp

#加入路径
EXCEL_LIBRARY_LOCATION = $$PWD
INCLUDEPATH += $$EXCEL_LIBRARY_LOCATION
DEPENDPATH += $$EXCEL_LIBRARY_LOCATION

