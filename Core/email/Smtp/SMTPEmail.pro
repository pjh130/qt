#-------------------------------------------------
#
# Project created by QtCreator 2011-08-11T20:59:25
#
#-------------------------------------------------

QT       += core network

TARGET = SMTPEmail

# Build as an application
#TEMPLATE = app

# Build as a library
TEMPLATE = lib
DEFINES += SMTP_BUILD
win32:CONFIG += dll

SMTP_HEADER_PATH = $$PWD/../header

INCLUDEPATH += $$SMTP_HEADER_PATH

CONFIG(release, debug|release) {
    DESTDIR = $$PWD/../lib/release
}
CONFIG(debug,debug|release) {
    DESTDIR = $$PWD/../lib/debug
}

SOURCES += \
    src/emailaddress.cpp \
    src/mimeattachment.cpp \
    src/mimefile.cpp \
    src/mimehtml.cpp \
    src/mimeinlinefile.cpp \
    src/mimemessage.cpp \
    src/mimepart.cpp \
    src/mimetext.cpp \
    src/smtpclient.cpp \
    src/quotedprintable.cpp \
    src/mimemultipart.cpp \
    src/mimecontentformatter.cpp \

HEADERS  += \
    $$SMTP_HEADER_PATH/emailaddress.h \
    $$SMTP_HEADER_PATH/mimeattachment.h \
    $$SMTP_HEADER_PATH/mimefile.h \
    $$SMTP_HEADER_PATH/mimehtml.h \
    $$SMTP_HEADER_PATH/mimeinlinefile.h \
    $$SMTP_HEADER_PATH/mimemessage.h \
    $$SMTP_HEADER_PATH/mimepart.h \
    $$SMTP_HEADER_PATH/mimetext.h \
    $$SMTP_HEADER_PATH/smtpclient.h \
    $$SMTP_HEADER_PATH/SmtpMime \
    $$SMTP_HEADER_PATH/quotedprintable.h \
    $$SMTP_HEADER_PATH/mimemultipart.h \
    $$SMTP_HEADER_PATH/mimecontentformatter.h \
    $$SMTP_HEADER_PATH/smtpexports.h

OTHER_FILES += \
    LICENSE \
    README.md

FORMS +=
