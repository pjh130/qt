#useage:
#include($$PWD/xxx.pri)

include(D:\Code\Go\src\github.com\pjh130\qt\Core\email\email.pri)

# Location
LOG_LIBRARY_LOCATION = $$PWD

INCLUDEPATH += $$LOG_LIBRARY_LOCATION
DEPENDPATH += $$LOG_LIBRARY_LOCATION

HEADERS += \
    $$PWD/logex.h

SOURCES += \
    $$PWD/logex.cpp


