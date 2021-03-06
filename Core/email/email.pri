#useage:
#include($$PWD/xxx.pri)

# Location of SMTP Library
SMTP_LIBRARY_LOCATION = $$PWD

HEADERS += \
    $$PWD/emailex.h

SOURCES += \
    $$PWD/emailex.cpp

win32:CONFIG(release, debug|release): LIBS += -L$$SMTP_LIBRARY_LOCATION/lib/release/ -lSMTPEmail
else:win32:CONFIG(debug, debug|release): LIBS += -L$$SMTP_LIBRARY_LOCATION/lib/debug/ -lSMTPEmail
else:unix: LIBS += -L$$SMTP_LIBRARY_LOCATION -lSMTPEmail

INCLUDEPATH += $$SMTP_LIBRARY_LOCATION
INCLUDEPATH += $$SMTP_LIBRARY_LOCATION/header
DEPENDPATH += $$SMTP_LIBRARY_LOCATION

