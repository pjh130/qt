#useage:
#include($$PWD/xxx.pri)

# Location of SMTP Library
SMTP_LIBRARY_LOCATION = $$PWD

win32:CONFIG(release, debug|release): LIBS += -L$$SMTP_LIBRARY_LOCATION/lib/release/ -lSMTPEmail
else:win32:CONFIG(debug, debug|release): LIBS += -L$$SMTP_LIBRARY_LOCATION/lib/debug/ -lSMTPEmail
else:unix: LIBS += -L$$SMTP_LIBRARY_LOCATION -lSMTPEmail

INCLUDEPATH += $$SMTP_LIBRARY_LOCATION
INCLUDEPATH += $$SMTP_LIBRARY_LOCATION/header
DEPENDPATH += $$SMTP_LIBRARY_LOCATION

#OTHER_FILES += demos

HEADERS += \
    $$PWD/email.h

SOURCES += \
    $$PWD/email.cpp

