#. =================>一些特殊调用
#添加生成程序的详细信息描述
VERSION = 1.0 
QMAKE_TARGET_PRODUCT = "product"               #用于指定产品名称                                         
QMAKE_TARGET_COMPANY = "panpan"                #用于指定生产商
QMAKE_TARGET_COPYRIGHT = "Copyright (C) panpan <hello@xxx.com>"  #用于声明版权
QMAKE_TARGET_DESCRIPTION = "xxxxxxxxx"         #用于描述应用程序

TARGET      	=  pksystem   #生成的程序名
DESTDIR     	+= bin        #生成的应用程序放置的目录
UI_DIR      	=  temp/ui    #指定uic命令将.ui文件转化成ui_*.h文件的存放的目录
OBJECTS_DIR 	=  temp/obj   #指定目标文件(obj)的存放目录
MOC_DIR     	=  temp/moc   #指定moc命令将含Q_OBJECT的头文件转换成标准.h文件的存放目录
RCC_DIR     	=  temp/rcc   #指定rcc命令将.qrc文件转换成qrc_*.h文件的存放目录
CODECFORTR      = UTF-8       #源文件编码方式GBK，UTF-8
CODECFORSRC 	= GBK         #源文件编码方式GBK，UTF-8

DEPENDPATH+= . forms include  #程序编译时依赖的相关路径
QT += core widgets network    #用到相关的类，那么需要包含相应的模块
INCLUDEPATH+= ./header        #头文件包含路径
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

#QT版本的差异化
greaterThan(QT_MAJOR_VERSION, 4){
    QT += widgets
    message("test ...")
}else{
    message("pla,pla,pla ....")
}
lessThan(QT_MAJOR_VERSION, 5) {
    message("Cannot build current QtSerialPort sources with Qt version $${QT_VERSION}.")
    error("Use at least Qt 5.0.0 or try to download QtSerialPort for Qt4.")
}

load(configure)         #没用过，待怎加使用说明
load(qt_parts)          #没用过，待怎加使用说明
load(qt_build_config)   #没用过，待怎加使用说明
load(qt_module)         #没用过，待怎加使用说明

#变量用法：
MY_VARIABLE = value
MY_DEFINES = $$DEFINES 或者 MY_DEFINES = $${DEFINES}

# use INSTALL_ROOT to modify the install location
headers.files = $$PUBLIC_HEADERS
headers.path = $$[QT_INSTALL_HEADERS]
target.path = $$[QT_INSTALL_LIBS]
INSTALLS += target headers

#. =================>模板变量告诉qmake为这个应用程序生成哪种makefile
TEMPLATE = app
	 #A> app -建立一个应用程序的makefile。这是默认值，所以如果模板没有被指定，这个将被使用。
	 #B> lib - 建立一个库的makefile。
	 #C> vcapp - 建立一个应用程序的VisualStudio项目文件。
	 #D> vclib - 建立一个库的VisualStudio项目文件。
	 #E> subdirs -这是一个特殊的模板，它可以创建一个能够进入特定目录并且为一个项目文件生成makefile并且为它调用make的makefile。
	 #TEMPLATE=subdirs
	 #SUBDIRS=quazip qztest
	 #qztest.depends = quazip
	 
	 #exists($$_PRO_FILE_PWD_/src/src.pro) {
		 #sub_src.subdir = src
		 #sub_src.target = sub-src
		 #SUBDIRS += sub_src
		#exists($$_PRO_FILE_PWD_/tools/tools.pro) {
			 #sub_tools.subdir = tools
			 #sub_tools.target = sub-tools
			 #sub_tools.depends = sub_src
			 # conditional treatment happens on a case-by-case basis
			 #SUBDIRS += sub_tools
		#}
	 #}
  
#. =================>配置信息 CONFIG用来告诉qmake关于应用程序的配置信息。
CONFIG+= qt warn_on release
    #在这里使用“+=”，是因为我们添加我们的配置选项到任何一个已经存在中。这样做比使用“=”那样替换已经指定的所有选项是更安全的。
	#  选项	说明
	#1、控制编译器标志的选项：
	#  warn_on	编译器应该输出尽可能多的警告。如果也指定了warn_off，最后一个生效。
	#  warn_off	编译器应该输出尽可能少的警告。
	#  release	项目以release模式构建。如果也指定了debug，那么最后一个生效。
	#  debug	项目以debug模式构建。
	#  debug_and_release	项目准备以debug和release两种模式构建。
	#  debug_and_release_target	此选项默认设置。如果也指定了debug_and_release，最终的debug和release构建在不同的目录。
	#  build_all	如果指定了debug_and_release，默认情况下，该项目会构建为debug和release模式。
	#  autogen_precompile_source	自动生成一个.cpp文件，包含在.pro中指定的预编译头文件。
	#  当使用debug和release选项时(Windows下默认的)，该项目将被处理三次：一次生成一个”meta”Makefile，另外两次生成Makefile.Debug和Makefile.Release。
	#  在后面的次数，build_pass和相应的debug或release添加到CONFIG选项。这使得它可以执行构建特定任务。
	#  例如：
	#  build_pass:CONFIG(debug, debug|release) {
	#      unix: TARGET = $$join(TARGET,,,_debug)
	#      else: TARGET = $$join(TARGET,,,d)
	#  }
	#2、控制需要连接的库的选项：
	#  dll          是指动态编译库。
	#  staticlib    是指静态编译库
	#  plugin       是指编译一个插件，插件总是动态库，因此这一参数暗指 dll 参数
	#  console      是指应用程序需要写控制台（使用 cout，cerr，qWarning()，等等）
	#  ordered	使用subdirs模板时，此选项指定应该按照目录列表的顺序处理它们。
	#  precompile_header	可以在项目中使用预编译头文件的支持。
	#  exceptions	启用异常支持。默认设置。
	#  exceptions_off	禁用异常支持。
	#  rtti	启用RTTI支持。默认情况下，使用编译器默认。
	#  rtti_off	禁用RTTI支持。默认情况下，使用编译器默认。
	#  stl	启用STL支持。默认情况下，使用编译器默认。
	#  stl_off	禁用STL支持。默认情况下，使用编译器默认。
	#  thread	启用线程支持。当CONFIG包括qt时启用，这是缺省设置。
	#  c++11	启用c++11支持。如果编译器不支持c++11这个选项，没有影响。默认情况下，支持是禁用的。
	#  c++14	启用c++14支持。如果编译器不支持c++14这个选项，没有影响。默认情况下，支持是禁用的。


#. =================>平台相关性处理 我们在这里需要做的是根据qmake所运行的平台来使用相应的作用域来进行处理
#win32/macx/unix/linux-g++等
win32{
}
win64{
}
unix{
}
macx{
}

#. =================>常用函数
#1、contains( variablename, value )：
#　　如果value存在于一个被叫做variablename的变量的值的列表中，那么成功，否则失败。例如：
#　　contains( CONFIG, thread ) {
#　　　　DEFINES += QT_THREAD_SUPPORT
#　　}
#　　如果thread存在于CONFIG变量的值的列表中时，那么QT_THREAD_SUPPORT将会被加入到DEFINES变量的值的列表中。
#2、count( variablename, number )：
#　　如果number与一个被叫做variablename的变量的值的数量一致，那么成功，否则失败。例如：
#　　count( DEFINES, 5 ) {
#　　　　CONFIG += debug
#　　}
#3、dirname(file)：
#　　返回指定文件的目录名称。例如：
#　　 FILE = /etc/X11R6/XF86Config
#　　 DIRNAME = $$dirname(FILE) #/etc/X11R6
#4、error( string )：
#　　这个函数输出所给定的字符串，然后会使qmake退出。例如：
#　　error(An error has occurred in the configuration process.)
#5、exists( filename )：
#　　如果指定文件存在，那么函数成功，否则失败。例如：
#　　exists( /local/qt/qmake/main.cpp ) {
#　　　　SOURCES += main.cpp
#　　}
#　　如果/local/qt/qmake/main.cpp存在，那么main.cpp将会被添加到源文件列表中。
#　　注意可以不用考虑平台使用“/”作为目录的分隔符。
#6、find( variablename, substr )：
#　　这将会放置variablename中所有匹配substr的值。substr也可以是正则表达式，而因此将被匹配。
#　　MY_VAR = one two three four
#　　MY_VAR2 = $$join(MY_VAR, " -L", -L) -Lfive
#　　MY_VAR3 = $$member(MY_VAR, 2) $$find(MY_VAR, t.*)
#　　MY_VAR2将会包含“-Lone -Ltwo -Lthree -Lfour -Lfive”，并且MYVAR3将会包含“three two three”。
#7、include(filename)：
#　　包含文件。
#8、infile( filename, var, val )：
#　　如果filename文件（当它被qmake自己解析时）包含一个值为val的变量var，那么这个函数将会返回成功。你也可以不传递第三个参数（val），这时函数将只测试文件中是否分配有这样一个变量var。
#9、isEmpty( variablename )：
#　　这和使用count( variablename, 0 )是一样的。如果叫做variablename的变量没有任何元素，函数返回成功否则失败。例如：
#　　isEmpty( CONFIG ) {
#　　　　CONFIG += qt warn_on debug
#　　}
#10、join( variablename, glue, before, after )：
#　　这将会在variablename的各个值中间加入glue。如果这个变量的值为非空，那么就会在值的前面加一个前缀before和一个后缀after。只有variablename是必须的字段，其它默认情况下为空串。如果你需要在glue、before或者after中使用空格的话，你必须提供（引用？）它们。
#11、member( variablename, position )：
#　　返回函数的值列表中指定位置的值。如果变量值列表并不存在指定的位置，这将会返回一个空串。variablename是唯一必须的字段，如果没有指定位置，则默认为列表中的第一个值（position默认为0）。
#12、message( string )：
#　　这个函数只是简单地在控制台上输出消息。
#    　　message( "This is a message" )
#　　文本“This is a message”被输出到控制台上并且对于项目文件的处理将会继续进行。
#13、replace(string, old_string, new_string)：
#　　用讲string中的old_string用new_string代替，例如：
#　　MESSAGE = This is a tent.
#　　message($$replace(MESSAGE, tent, test))
#　　prints the message:
#　　This is a test.
#14、system( command )：
#　　特定指令被执行并且如果它返回一个1的退出值，那么函数成功否则失败。例如：
#　　system( ls /bin ) {
#　　　　SOURCES += bin/main.cpp
#　　　　HEADERS += bin/main.h
#　　}
#	system( cd $$PWD )
#	system( python autoRelease.py )
#　　所以如果命令ls /bin返回1，那么bin/main.cpp将被添加到源文件列表中并且bin/main.h将被添加到头文件列表中。
#15、warning(string)：
#　　这个函数一直返回成功，并且会输出指定字符串给用户，跟message是同义词。

















