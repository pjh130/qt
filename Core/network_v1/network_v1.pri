#useage:
#include($$PWD/xxx.pri)

QT += network

# Location
NETWORK_LIBRARY_LOCATION = $$PWD

INCLUDEPATH += $$NETWORK_LIBRARY_LOCATION
DEPENDPATH += $$NETWORK_LIBRARY_LOCATION

HEADERS += \
    $$PWD/networkaccessmanagerex.h \
    $$PWD/udpex.h

SOURCES += \
    $$PWD/networkaccessmanagerex.cpp \
    $$PWD/udpex.cpp



