TARGET = json
TEMPLATE = lib

CONFIG += staticlib

QJSON_HEADER_PATH = $$PWD/../header

INCLUDEPATH += $$QJSON_HEADER_PATH

CONFIG(release, debug|release) {
    DESTDIR = $$PWD/../lib/release
}
CONFIG(debug,debug|release) {
    DESTDIR = $$PWD/../lib/debug
}

#VERSION = 0.7.1

PRIVATE_HEADERS += \
  $$QJSON_HEADER_PATH/json_parser.hh \
  $$QJSON_HEADER_PATH/json_scanner.h \
  $$QJSON_HEADER_PATH/location.hh \
  $$QJSON_HEADER_PATH/parser_p.h  \
  $$QJSON_HEADER_PATH/position.hh \
  $$QJSON_HEADER_PATH/qjson_debug.h  \
  $$QJSON_HEADER_PATH/stack.hh

PUBLIC_HEADERS += \
  $$QJSON_HEADER_PATH/parser.h \
  $$QJSON_HEADER_PATH/parserrunnable.h \
  $$QJSON_HEADER_PATH/qobjecthelper.h \
  $$QJSON_HEADER_PATH/serializer.h \
  $$QJSON_HEADER_PATH/serializerrunnable.h \
  $$QJSON_HEADER_PATH/qjson_export.h

HEADERS += $$PRIVATE_HEADERS $$PUBLIC_HEADERS

SOURCES += \
  json_parser.cc \
  json_scanner.cpp \
  parser.cpp \
  parserrunnable.cpp \
  qobjecthelper.cpp \
  serializer.cpp \
  serializerrunnable.cpp
