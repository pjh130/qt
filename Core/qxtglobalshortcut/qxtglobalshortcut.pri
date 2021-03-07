#加入路径
SHORTCUT_LIBRARY_LOCATION = $$PWD
INCLUDEPATH += $$SHORTCUT_LIBRARY_LOCATION
DEPENDPATH += $$SHORTCUT_LIBRARY_LOCATION

HEADERS += $$PWD/qxtglobal.h \
           $$PWD/qxtglobalshortcut.h \
           $$PWD/qxtglobalshortcut_p.h
SOURCES += $$PWD/qxtglobalshortcut.cpp
win32{
    SOURCES += $$PWD/qxtglobalshortcut_win.cpp
    LIBS += -luser32
}
unix:SOURCES += $$PWD/qxtglobalshortcut_x11.cpp
mac:SOURCES += $$PWD/qxtglobalshortcut_mac.cpp
