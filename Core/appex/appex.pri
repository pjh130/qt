#useage:
#include($$PWD/xxx.pri)

#加入路径
APP_LIBRARY_LOCATION = $$PWD
INCLUDEPATH += $$APP_LIBRARY_LOCATION
DEPENDPATH += $$APP_LIBRARY_LOCATION

HEADERS += \
    $$PWD/appex.h

SOURCES += \
    $$PWD/appex.cpp

