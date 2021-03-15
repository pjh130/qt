#useage:
#include($$PWD/xxx.pri)

QT += network

include(D:\Code\Go\src\github.com\pjh130\qt\Core\ThreadHandle\threadhandle.pri)

# Location
NETWORK_LIBRARY_LOCATION = $$PWD
INCLUDEPATH += $$NETWORK_LIBRARY_LOCATION
DEPENDPATH += $$NETWORK_LIBRARY_LOCATION

HEADERS += \
    $$PWD/ipex.h \
    $$PWD/netpublic.h \
    $$PWD/networkaccessmanagerex.h \
    $$PWD/tcpserver.h \
    $$PWD/tcpsocket.h \
    $$PWD/tcpsocketclient.h \
    $$PWD/tcpsocketthread.h \
    $$PWD/udpex.h

SOURCES += \
    $$PWD/ipex.cpp \
    $$PWD/netpublic.cpp \
    $$PWD/networkaccessmanagerex.cpp \
    $$PWD/tcpserver.cpp \
    $$PWD/tcpsocket.cpp \
    $$PWD/tcpsocketclient.cpp \
    $$PWD/tcpsocketthread.cpp \
    $$PWD/udpex.cpp


