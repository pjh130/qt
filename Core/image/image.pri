#useage:
#include($$PWD/xxx.pri)

#加入路径
IMAGE_LIBRARY_LOCATION = $$PWD
INCLUDEPATH += $$IMAGE_LIBRARY_LOCATION
DEPENDPATH += $$IMAGE_LIBRARY_LOCATION

HEADERS += \
    $$PWD/imageex.h

SOURCES += \
    $$PWD/imageex.cpp

