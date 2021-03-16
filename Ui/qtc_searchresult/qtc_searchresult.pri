
#加入路径
SEARCH_LIBRARY_LOCATION = $$PWD
INCLUDEPATH += $$SEARCH_LIBRARY_LOCATION
DEPENDPATH += $$SEARCH_LIBRARY_LOCATION

INCLUDEPATH += $$SEARCH_LIBRARY_LOCATION/header

CONFIG(release, debug|release) {
    LIBS += -L$$SEARCH_LIBRARY_LOCATION/lib/release/ -lqtc_searchresult
}
CONFIG(debug,debug|release) {
    LIBS += -L$$SEARCH_LIBRARY_LOCATION/lib/debug/ -lqtc_searchresult
}

HEADERS += \

SOURCES += \
