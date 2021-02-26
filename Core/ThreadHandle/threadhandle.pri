#useage:
#include($$PWD/xxx.pri)

HEADERS += \
        $$PWD/threadhandle.h
SOURCES += \
        $$PWD/threadhandle.cpp

# Location
THREAD_LIBRARY_LOCATION = $$PWD

INCLUDEPATH += $$THREAD_LIBRARY_LOCATION
DEPENDPATH += $$THREAD_LIBRARY_LOCATION

