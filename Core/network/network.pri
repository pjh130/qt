#useage:
#include($$PWD/xxx.pri)

QT += network

# Location
NETWORK_LIBRARY_LOCATION = $$PWD

INCLUDEPATH += $$NETWORK_LIBRARY_LOCATION
DEPENDPATH += $$NETWORK_LIBRARY_LOCATION

HEADERS += \
    $$PWD/ipex.h \
    $$PWD/networkaccessmanagerex.h \
    $$PWD/tcpserver.h \
    $$PWD/tcpsocket.h \
    $$PWD/udpex.h \
    $$PWD/threadhandle.h

SOURCES += \
    $$PWD/ipex.cpp \
    $$PWD/networkaccessmanagerex.cpp \
    $$PWD/tcpserver.cpp \
    $$PWD/tcpsocket.cpp \
    $$PWD/udpex.cpp \
    $$PWD/threadhandle.cpp


