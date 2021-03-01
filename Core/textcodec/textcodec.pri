#useage:
#include($$PWD/xxx.pri)

#★★★★★解决乱码的方法概括★★★★
#1、如果IDE是Qt Creator，把它的环境设置为“UTF-8+BOM”编码。
#2、如果IDE是Visual Studio，请下载插件，名称是ForceUTF8 (with BOM)，
#所有源文件和头文件都会保存为“UTF-8+BOM”编码。
#3、如果编译器是MSVC，请在预编译头stdafx.h文件加入
#    #if defined(_MSC_VER) && (_MSC_VER >= 1600)
#    # pragma execution_character_set("utf-8")
#    #endif
##或者添加QMAKE_CXXFLAGS += /utf-8到您的.pro文件中
#4、源码文件main函数入口设置中文编码
#    //设置字符集
#    TextCodecEx::setCodecForLocale();
#★★★★★解决乱码的方法概括★★★★

#加入路径
TEXTCODEC_LIBRARY_LOCATION = $$PWD
INCLUDEPATH += $$TEXTCODEC_LIBRARY_LOCATION
DEPENDPATH += $$TEXTCODEC_LIBRARY_LOCATION

HEADERS += \
    $$PWD/textcodecex.h

SOURCES += \
    $$PWD/textcodecex.cpp

