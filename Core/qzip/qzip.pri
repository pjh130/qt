#useage:
#include($$PWD/xxx.pri)

#修改成当前编译环境的实际路径
INCLUDEPATH += D:\Develop\Qt\5.15.2\msvc2019_64\include\QtZlib

# Location of SMTP Library
QZIP_LIBRARY_LOCATION = $$PWD

win32:CONFIG(release, debug|release): LIBS += -L$$QZIP_LIBRARY_LOCATION/lib/release/ -lquazip
else:win32:CONFIG(debug, debug|release): LIBS += -L$$QZIP_LIBRARY_LOCATION/lib/debug/ -lquazipd
else:unix: LIBS += -L$$QZIP_LIBRARY_LOCATION/lib -lquazip

INCLUDEPATH += $$QZIP_LIBRARY_LOCATION/header
DEPENDPATH += $$QZIP_LIBRARY_LOCATION



