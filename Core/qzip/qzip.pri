#useage:
#include($$PWD/xxx.pri)

#修改成当前编译环境的实际路径
INCLUDEPATH += D:\Develop\Qt5.7\5.7\msvc2013_64\include\QtZlib

# Location of SMTP Library
SMTP_LIBRARY_LOCATION = $$PWD

win32:CONFIG(release, debug|release): LIBS += -L$$SMTP_LIBRARY_LOCATION/release/ -lquazip
else:win32:CONFIG(debug, debug|release): LIBS += -L$$SMTP_LIBRARY_LOCATION/debug/ -lquazip
else:unix: LIBS += -L$$SMTP_LIBRARY_LOCATION -lquazip

INCLUDEPATH += $$SMTP_LIBRARY_LOCATION/header
DEPENDPATH += $$SMTP_LIBRARY_LOCATION



