#useage:
#include($$PWD/xxx.pri)

#加入路径
OS_LIBRARY_LOCATION = $$PWD
INCLUDEPATH += $$OS_LIBRARY_LOCATION
DEPENDPATH += $$OS_LIBRARY_LOCATION

HEADERS += \
    $$PWD/systemex.h

SOURCES += \
    $$PWD/systemex.cpp
