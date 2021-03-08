#1. =================>一些特殊调用
#外部预处理
system( cd $$PWD )
system( python autoRelease.py )

#QT版本的差异化
greaterThan(QT_MAJOR_VERSION, 4){
    QT += widgets
    message("test ...")
}else{
    message("pla,pla,pla ....")
}

#CODECFORSRC：源文件编码方式GBK，UTF-8
CODECFORTR = UTF-8
CODECFORSRC = GBK

#VERSION：指定目标库版本号
VERSION = 1.0

# use INSTALL_ROOT to modify the install location
headers.files = $$PUBLIC_HEADERS
headers.path = $$[QT_INSTALL_HEADERS]
target.path = $$[QT_INSTALL_LIBS]
INSTALLS += target headers

#2. =================>模板变量告诉qmake为这个应用程序生成哪种makefile
TEMPLATE = app
  #A> app -建立一个应用程序的makefile。这是默认值，所以如果模板没有被指定，这个将被使用。
  #B> lib - 建立一个库的makefile。
  #C> vcapp - 建立一个应用程序的VisualStudio项目文件。
  #D> vclib - 建立一个库的VisualStudio项目文件。
  #E> subdirs -这是一个特殊的模板，它可以创建一个能够进入特定目录并且为一个项目文件生成makefile并且为它调用make的makefile。
  #TEMPLATE=subdirs
  #SUBDIRS=quazip qztest
  #qztest.depends = quazip

#3. =================>指定的目录
DESTDIR    += bin       #生成的应用程序放置的目录
UI_DIR      = temp/ui   #指定uic命令将.ui文件转化成ui_*.h文件的存放的目录
OBJECTS_DIR = temp/obj  #指定目标文件(obj)的存放目录
MOC_DIR     = temp/moc  #指定moc命令将含Q_OBJECT的头文件转换成标准.h文件的存放目录
RCC_DIR     = temp/rcc  #指定rcc命令将.qrc文件转换成qrc_*.h文件的存放目录

#4. =================>指定生成的应用程序名
TARGET= pksystem

#5. =================>配置信息 CONFIG用来告诉qmake关于应用程序的配置信息。
CONFIG+= qt warn_on release
  #在这里使用“+=”，是因为我们添加我们的配置选项到任何一个已经存在中。这样做比使用“=”那样替换已经指定的所有选项是更安全的。
#  选项	说明
#  dll          是指动态编译库。
#  staticlib    是指静态编译库
#  plugin       是指编译一个插件，插件总是动态库，因此这一参数暗指 dll 参数
#  console      是指应用程序需要写控制台（使用 cout，cerr，qWarning()，等等）
#  release	项目以release模式构建。如果也指定了debug，那么最后一个生效。
#  debug	项目以debug模式构建。
#  debug_and_release	项目准备以debug和release两种模式构建。
#  debug_and_release_target	此选项默认设置。如果也指定了debug_and_release，最终的debug和release构建在不同的目录。
#  build_all	如果指定了debug_and_release，默认情况下，该项目会构建为debug和release模式。
#  autogen_precompile_source	自动生成一个.cpp文件，包含在.pro中指定的预编译头文件。
#  ordered	使用subdirs模板时，此选项指定应该按照目录列表的顺序处理它们。
#  precompile_header	可以在项目中使用预编译头文件的支持。
#  warn_on	编译器应该输出尽可能多的警告。如果也指定了warn_off，最后一个生效。
#  warn_off	编译器应该输出尽可能少的警告。
#  exceptions	启用异常支持。默认设置。
#  exceptions_off	禁用异常支持。
#  rtti	启用RTTI支持。默认情况下，使用编译器默认。
#  rtti_off	禁用RTTI支持。默认情况下，使用编译器默认。
#  stl	启用STL支持。默认情况下，使用编译器默认。
#  stl_off	禁用STL支持。默认情况下，使用编译器默认。
#  thread	启用线程支持。当CONFIG包括qt时启用，这是缺省设置。
#  c++11	启用c++11支持。如果编译器不支持c++11这个选项，没有影响。默认情况下，支持是禁用的。
#  c++14	启用c++14支持。如果编译器不支持c++14这个选项，没有影响。默认情况下，支持是禁用的。
#  当使用debug和release选项时(Windows下默认的)，该项目将被处理三次：一次生成一个”meta”Makefile，另外两次生成Makefile.Debug和Makefile.Release。
#  在后面的次数，build_pass和相应的debug或release添加到CONFIG选项。这使得它可以执行构建特定任务。
#  例如：
#  build_pass:CONFIG(debug, debug|release) {
#      unix: TARGET = $$join(TARGET,,,_debug)
#      else: TARGET = $$join(TARGET,,,d)
#  }

#6. =================>程序编译时依赖的相关路径
DEPENDPATH+= . forms include qrc sources

#7. =================>头文件包含路径
INCLUDEPATH+= ./header

#8. =================>工程中包含的文件
QT += core widgets network    #用到相关的类，那么需要包含相应的模块
HEADERS+= include/xxx.h       #头文件
FORMS+= forms/xxx.ui          #UI文件
SOURCES+= sources/xxx.cpp     #源文件
RESOURCES+= qrc/xxx.qrc       #资源文件
TRANSLATIONS += xxx/xxx.ts    #指定包含用户界面翻译文本的翻译(.ts)文件列表

DEFINES+= XX_XX_XXX           #定义编译选项，在.h文件中就可以使用：#ifdefine xx_xx_xxx
RC_FILE= xxx.icns             #指定应用程序资源文件的名称
RC_ICONS = xxx.ico            #仅适用于Windows，指定的图标应该包含在一个生成的.rc文件里。如果RC_FILE 和RES_FILE变量都没有设置这才可利用
OTHER_FILES += Res/gray.qss   #其他文件
include(/Cores/xxx.pri)       #添加pri工程文件
LIBS+= -L folderPath          #引入的lib文件的路径-L：引入路径(例子: LIBS += -L$$PWD/release/ -lquazip)
CONFIG(release, debug|release) {
    LIBS += -L$$PWD/release -lCaptureScreen
}
else:CONFIG(debug,debug|release) {
    LIBS += -L$$PWD/debug -lCaptureScreend
}
mac: LIBS += -framework Carbon
else:win32: LIBS += -luser32
else:unix {
	QT += x11extras
	LIBS += -lX11
}

#9. =================>平台相关性处理 我们在这里需要做的是根据qmake所运行的平台来使用相应的作用域来进行处理
win32{
    INCLUDEPATH += $$PWD/Cores
}
win64{
    DEFINES += XXX_WIN64  #定义编译选项，在.h文件中就可以使用#ifdefine XXX_WIN64
}
unix{
    INCLUDEPATH += $$PWD/Cores
}
macx{
    DEFINES += XXX_MAC   #定义编译选项，在.h文件中就可以使用#ifdefine XXX_MAC
}


















