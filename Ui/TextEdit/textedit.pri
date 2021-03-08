#useage:
#include($$PWD/xxx.pri)

#加入路径
TEXTEDIT_LIBRARY_LOCATION = $$PWD
INCLUDEPATH += $$TEXTEDIT_LIBRARY_LOCATION
DEPENDPATH += $$TEXTEDIT_LIBRARY_LOCATION

HEADERS += \
    $$PWD/texteditex.h

SOURCES += \
    $$PWD/texteditex.cpp


