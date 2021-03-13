#====仅仅是个人总结用，部分代码来别人的成果，非常感谢原作者====
#  所有涉及的原作者有如下（如果有遗漏会补上）：
#    1. xiehechong
#    2. 

#useage:
#include($$PWD/xxx.pri)

#VERSION = 1.0
#QMAKE_TARGET_PRODUCT = "product"
#QMAKE_TARGET_COMPANY = "panpan"
#QMAKE_TARGET_COPYRIGHT = "Copyright (C) panpan <hello@xxx.com>"
#QMAKE_TARGET_DESCRIPTION = "panpan personal"

include(D:\Code\Go\src\github.com\pjh130\qt\Ui\CaptureScreen\CaptureScreen.pri)
include(D:\Code\Go\src\github.com\pjh130\qt\Ui\TextEdit\textedit.pri)

#加入路径
UI_LIBRARY_LOCATION = $$PWD
INCLUDEPATH += $$UI_LIBRARY_LOCATION
DEPENDPATH += $$UI_LIBRARY_LOCATION
