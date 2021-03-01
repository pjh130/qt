#useage:
#include($$PWD/xxx.pri)

#加入路径
SETTINGS_LIBRARY_LOCATION = $$PWD
INCLUDEPATH += $$SETTINGS_LIBRARY_LOCATION
DEPENDPATH += $$SETTINGS_LIBRARY_LOCATION

HEADERS += \
    $$PWD/settingsex.h

SOURCES += \
    $$PWD/settingsex.cpp


