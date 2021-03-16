QT += widgets

TARGET = qtc_searchresult
TEMPLATE = lib

CONFIG += staticlib

SEARCH_HEADER_PATH = $$PWD/../header

INCLUDEPATH += $$SEARCH_HEADER_PATH

CONFIG(release, debug|release) {
    DESTDIR = $$PWD/../lib/release
}
CONFIG(debug,debug|release) {
    DESTDIR = $$PWD/../lib/debug
}

HEADERS += \ 
    $$SEARCH_HEADER_PATH/searchresultcolor.h \
    $$SEARCH_HEADER_PATH/searchresulttreeitemdelegate.h \
    $$SEARCH_HEADER_PATH/searchresulttreeitemroles.h \
    $$SEARCH_HEADER_PATH/searchresulttreeitems.h \
    $$SEARCH_HEADER_PATH/searchresulttreemodel.h \
    $$SEARCH_HEADER_PATH/searchresulttreeview.h \
    $$SEARCH_HEADER_PATH/searchresultitem.h \
    $$SEARCH_HEADER_PATH/searchresultitem.h \
    $$SEARCH_HEADER_PATH/searchresultwidget.h

SOURCES += \ 
    searchresulttreeitemdelegate.cpp \
    searchresulttreeitems.cpp \
    searchresulttreemodel.cpp \
    searchresulttreeview.cpp \
    searchresultwidget.cpp

RESOURCES +=
