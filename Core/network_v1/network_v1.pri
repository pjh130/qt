#useage:
#include($$PWD/xxx.pri)

QT += network

# Location
NETWORK_LIBRARY_LOCATION = $$PWD

INCLUDEPATH += $$NETWORK_LIBRARY_LOCATION
DEPENDPATH += $$NETWORK_LIBRARY_LOCATION

HEADERS += \
    $$PWD/networkaccessmanagerex.h

SOURCES += \
    $$PWD/networkaccessmanagerex.cpp



