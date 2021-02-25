#useage:
#include($$PWD/xxx.pri)

# Location of SMTP Library
SMTP_LIBRARY_LOCATION = $$PWD

INCLUDEPATH += $$SMTP_LIBRARY_LOCATION
DEPENDPATH += $$SMTP_LIBRARY_LOCATION

HEADERS += \
    $$PWD/logex.h

SOURCES += \
    $$PWD/logex.cpp


