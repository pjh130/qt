#useage:
#include($$PWD/xxx.pri)

#加入路径
TIME_LIBRARY_LOCATION = $$PWD
INCLUDEPATH += $$TIME_LIBRARY_LOCATION
DEPENDPATH += $$TIME_LIBRARY_LOCATION

HEADERS += \
    $$PWD/timeex.h \
    $$PWD/lunarcalendarinfo.h

SOURCES += \
    $$PWD/timeex.cpp \
    $$PWD/lunarcalendarinfo.cpp

