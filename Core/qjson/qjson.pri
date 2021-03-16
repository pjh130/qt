#useage:
#include($$PWD/xxx.pri)

#include($$PWD/qjson/src.pro)
#depends = src

#加入路径
QJSON_LIBRARY_LOCATION = $$PWD
INCLUDEPATH += $$QJSON_LIBRARY_LOCATION
DEPENDPATH += $$QJSON_LIBRARY_LOCATION

INCLUDEPATH += $$QJSON_LIBRARY_LOCATION/header

CONFIG(release, debug|release) {
    LIBS += -L$$QJSON_LIBRARY_LOCATION/lib/release/ -ljson
}
CONFIG(debug,debug|release) {
    LIBS += -L$$QJSON_LIBRARY_LOCATION/lib/debug/ -ljson
}

HEADERS += \

SOURCES += \

