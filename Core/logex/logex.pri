#useage:
#include($$PWD/xxx.pri)

include(D:\Code\Go\src\github.com\pjh130\qt\Core\email\email.pri)

# Location
LOG_LIBRARY_LOCATION = $$PWD

INCLUDEPATH += $$LOG_LIBRARY_LOCATION
DEPENDPATH += $$LOG_LIBRARY_LOCATION

#============================================================
#QMessageLogContext的context.file和context.line为空的解决方案
#QDebug版本是可以输出日志信息的，但在Release中输入日志的文件信息和行数为空。原因是，
#Qt在Release版本默认舍弃了文件信息、行数等信息。
#解决方案：
#    定义一个宏：
DEFINES += QT_MESSAGELOGCONTEXT
#============================================================

HEADERS += \
    $$PWD/logex.h

SOURCES += \
    $$PWD/logex.cpp


