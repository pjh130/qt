#useage:
#include($$PWD/xxx.pri)

QT += sql

# Location
QTSQL_LIBRARY_LOCATION = $$PWD

INCLUDEPATH += $$QTSQL_LIBRARY_LOCATION
DEPENDPATH += $$QTSQL_LIBRARY_LOCATION

HEADERS += \
    $$PWD/sqliteex.h \
    $$PWD/mysqlex.h \
    $$PWD/dbbase.h

SOURCES += \
    $$PWD/sqliteex.cpp \
    $$PWD/mysqlex.cpp \
    $$PWD/dbbase.cpp




