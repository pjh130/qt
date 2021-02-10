QT += core
QT -= gui

CONFIG += c++11

TARGET = zip
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

win32:CONFIG(release, debug|release): LIBS += -LG:\gopath\src\github.com\pjh130\qt\common\quazip\quazip\release -lquazip
else:win32:CONFIG(debug, debug|release): LIBS += -LG:\gopath\src\github.com\pjh130\qt\common\quazip\quazip\debug -lquazipd

INCLUDEPATH += G:\gopath\src\github.com\pjh130\qt\common\quazip\quazip
INCLUDEPATH += E:\develop\Qt\Qt5.7.0\5.7\msvc2013_64\include\QtZlib

SOURCES += main.cpp
