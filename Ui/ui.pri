#====仅仅是个人总结用，部分代码来别人的成果，非常感谢原作者====
#  所有涉及的原作者有如下（如果有遗漏会补上）：
#    1. xiehechong
#    2. shuaishishu

#useage:
#include($$PWD/xxx.pri)

#VERSION = 1.0
#QMAKE_TARGET_PRODUCT = "product"
#QMAKE_TARGET_COMPANY = "panpan"
#QMAKE_TARGET_COPYRIGHT = "Copyright (C) panpan <hello@xxx.com>"
#QMAKE_TARGET_DESCRIPTION = "panpan personal"

#UI_DIR      	=  temp/ui    #指定uic命令将.ui文件转化成ui_*.h文件的存放的目录
#OBJECTS_DIR 	=  temp/obj   #指定目标文件(obj)的存放目录
#MOC_DIR     	=  temp/moc   #指定moc命令将含Q_OBJECT的头文件转换成标准.h文件的存放目录
#RCC_DIR     	=  temp/rcc   #指定rcc命令将.qrc文件转换成qrc_*.h文件的存放目录

include(D:\Code\Go\src\github.com\pjh130\qt\Ui\CaptureScreen\CaptureScreen.pri)
include(D:\Code\Go\src\github.com\pjh130\qt\Ui\TextEdit\textedit.pri)
include(D:\Code\Go\src\github.com\pjh130\qt\Ui\framewindow\frame.pri)
include(D:\Code\Go\src\github.com\pjh130\qt\Ui\qtc_searchresult\qtc_searchresult.pri)


#加入路径
UI_LIBRARY_LOCATION = $$PWD
INCLUDEPATH += $$UI_LIBRARY_LOCATION
DEPENDPATH += $$UI_LIBRARY_LOCATION
