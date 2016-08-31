QT += core
QT -= gui

CONFIG += c++11

TARGET = AppIcon
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp

RESOURCES += \
    myapp.qrc

#{{Windows Execute File ICON and information setting}}#
win32{RC_FILE = Resources.rc}
