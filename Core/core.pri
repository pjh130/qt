#====仅仅是个人总结用，部分代码来别人的成果，非常感谢原作者====
#  所有涉及的原作者有如下（如果有遗漏会补上）：
#    1. 天池共享源码库 Tianchi share library for Qt (C++)
#    2. moyannie

#useage:
#include($$PWD/xxx.pri)

#VERSION = 1.0
#QMAKE_TARGET_PRODUCT = "product"
#QMAKE_TARGET_COMPANY = "panpan"
#QMAKE_TARGET_COPYRIGHT = "Copyright (C) panpan <hello@xxx.com>"
#QMAKE_TARGET_DESCRIPTION = "panpan personal"

include(D:\Code\Go\src\github.com\pjh130\qt\Core\email\email.pri)
include(D:\Code\Go\src\github.com\pjh130\qt\Core\logex\logex.pri)
include(D:\Code\Go\src\github.com\pjh130\qt\Core\network\network.pri)
include(D:\Code\Go\src\github.com\pjh130\qt\Core\ThreadHandle\threadhandle.pri)
include(D:\Code\Go\src\github.com\pjh130\qt\Core\excel\excel.pri)
include(D:\Code\Go\src\github.com\pjh130\qt\Core\qzip\qzip.pri)
include(D:\Code\Go\src\github.com\pjh130\qt\Core\qtsql\qtsql.pri)
include(D:\Code\Go\src\github.com\pjh130\qt\Core\file\file.pri)
include(D:\Code\Go\src\github.com\pjh130\qt\Core\time\time.pri)
include(D:\Code\Go\src\github.com\pjh130\qt\Core\image\image.pri)
include(D:\Code\Go\src\github.com\pjh130\qt\Core\string\string.pri)
include(D:\Code\Go\src\github.com\pjh130\qt\Core\os\os.pri)
include(D:\Code\Go\src\github.com\pjh130\qt\Core\textcodec\textcodec.pri)
include(D:\Code\Go\src\github.com\pjh130\qt\Core\settings\settings.pri)
include(D:\Code\Go\src\github.com\pjh130\qt\Core\QHotkey\qhotkey.pri)

#加入路径
CORE_LIBRARY_LOCATION = $$PWD
INCLUDEPATH += $$CORE_LIBRARY_LOCATION
DEPENDPATH += $$CORE_LIBRARY_LOCATION


