INCLUDEPATH += $$PWD
DEPENDPATH += $$PWD
QT       += core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets webkitwidgets

#if not compile with vs2008, commment the next line
HEADERS       += \
    $$PWD/windowframe.h \
    $$PWD/systemTrayIcon.h \
    $$PWD/qtwin.h \
    $$PWD/noframeDialog.h \
    $$PWD/comboButtonNucleus.h \
    $$PWD/combobutton.h \
    $$PWD/comboboxlist.h \
    $$PWD/comboboxitem.h \
    $$PWD/combobox.h \
    $$PWD/blurWindow.h \
    $$PWD/chatrecordwebview.h \
    $$PWD/comboitemlist.h \
    $$PWD/comboitem.h \
    $$PWD/searchbox.h \
    $$PWD/calculatemsgcount.h \
    $$PWD/skinlistwidget.h \
    $$PWD/skinitem.h \
    $$PWD/powerfultabwidget.h \
    $$PWD/onlinewidget.h \
    $$PWD/doubleLayerLable.h \
    $$PWD/hasDefaultTextEdit.h \
    $$PWD/searchMenuItem.h \
    $$PWD/searchBoxMenu.h \
    $$PWD/searchMenuExtendItem.h \
    $$PWD/public.h \
    $$PWD/numberButton.h \
    $$PWD/autoHideWindow.h \
    $$PWD/dynamicwidget.h

SOURCES       += \
    $$PWD/windowframe.cpp \
    $$PWD/systemTrayIcon.cpp \
    $$PWD/qtwin.cpp \
    $$PWD/noframeDialog.cpp \
    $$PWD/comboButtonNucleus.cpp \
    $$PWD/combobutton.cpp \
    $$PWD/comboboxlist.cpp \
    $$PWD/comboboxitem.cpp \
    $$PWD/combobox.cpp \
    $$PWD/blurWindow.cpp \
    $$PWD/chatrecordwebview.cpp \
    $$PWD/comboitemlist.cpp \
    $$PWD/comboitem.cpp \
    $$PWD/searchbox.cpp \
    $$PWD/calculatemsgcount.cpp \
    $$PWD/skinlistwidget.cpp \
    $$PWD/skinitem.cpp \
    $$PWD/powerfulTabwidget.cpp \
    $$PWD/onlinewidget.cpp \
    $$PWD/doubleLayerLable.cpp \
    $$PWD/hasDefaultTextEdit.cpp \
    $$PWD/searchMenuItem.cpp \
    $$PWD/searchBoxMenu.cpp \
    $$PWD/searchMenuExtendItem.cpp \
    $$PWD/numberButton.cpp \
    $$PWD/autoHideWindow.cpp \
    $$PWD/dynamicwidget.cpp \
    $$PWD/public.cpp

RESOURCES += \
    $$PWD/qt_controls_res.qrc

FORMS += \
    $$PWD/comboBoxItem.ui \
    $$PWD/comboBox.ui \
    $$PWD/searchBox.ui \
    $$PWD/searchMenuItem.ui \
    $$PWD/searchMenuExtendItem.ui \
    $$PWD/numberButton.ui
