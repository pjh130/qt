QT += core
QT -= gui

CONFIG += c++11

TARGET = zip
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

include(D:\Code\Go\src\github.com\pjh130\qt\common\qzip\qzip.pri)

#win32:CONFIG(release, debug|release): LIBS += -LG:\gopath\src\github.com\pjh130\qt\common\quazip\quazip\release -lquazip
#else:win32:CONFIG(debug, debug|release): LIBS += -LG:\gopath\src\github.com\pjh130\qt\common\quazip\quazip\debug -lquazipd

##修改成当前编译环境的实际路径
#INCLUDEPATH += D:\Code\Go\src\github.com\pjh130\qt\common\qzip\header
#INCLUDEPATH += D:\Develop\Qt5.7\5.7\msvc2013_64\include\QtZlib

SOURCES += main.cpp
