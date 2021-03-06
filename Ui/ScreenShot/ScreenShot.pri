#useage:
#include($$PWD/xxx.pri)

#加入路径
SCREESHOT_LIBRARY_LOCATION = $$PWD
INCLUDEPATH += $$SCREESHOT_LIBRARY_LOCATION
DEPENDPATH += $$SCREESHOT_LIBRARY_LOCATION

HEADERS += \
    $$PWD/fullscreenwidget.h

SOURCES += \
    $$PWD/fullscreenwidget.cpp
