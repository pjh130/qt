发布程序
==================
- <p>安装QT SDK 后，默认采用的是动态链接库的编译方式，如果需要发布程序，需要在可执行的文件中添加必须的动态链接库，然而有些动态链接库文件很大，这并不是我们想要的结果。
最好的办法是提交一个静态链接的程序。但是安装的Qt是动态编译的，要生成静态的版本，就需要自己重新进行编译。</p>

####.1. 静态编译
- l  优点，发布简单，单一文件。
- l  缺点，库文件很大，更新程序版本不方便。每次升级，都要重新分发所有的内容。

- 静态发布虽然不需要较多的dll，发布简单、方便，但是往往会牵扯到授权问题（详情请查看Qt LGPL授权），动态发布则可以避免。。。如果附带了Qt的dll，就相当于发布了Qt的dll，而這些库是属于Qt的，这足以保证使用者知道程序使用了LGPL版本的Qt。
 
- #### Windows平台静态编译
> 静态编译首先需要将
mingw平台静态编译，在编译Qt的时候，有个configure.exe程序，
configure.exe-static -platform win32-g++
可以产生静态编译项目文件。然后，
mingw32-makesub-src
就可以编译出静态库。如果只是用来分发程序，也可以mingw32-makerelease sub-src只编译一个静态库。
VC2015平台，在编译Qt的时候，configure.exe-static-platform win32-msvc2015
然后nmakesub-src或者nmake release sub-src完成静态编译。
再然后，就是把你的程序重新用静态编译的Qt再编译一次。
你会得到一个非常大的可执行程序。推荐使用AspPack压缩一下。就可以发给用户了。
 
- #### linux平台静态编译
> 1、下载源安装程序，如 qt-everywhere-opensource-src-5.5.1.tar.gz

> 2、解压到某一目录
> 
> 3、cd 进入解压后的目录，命令：
 
	./configure-static -release -qt-zlib -qt-gif -qt-libpng -qt-libmng -qt-libjpeg -nomakedemos -nomake examples -qt-sql-sqlite -prefix /usr/local/Trolltech/Qt-5.5.1_static
 
>参数-static 指的是要采用静态编译Qt的方法
参数-release指的是只编译release版本的库
参数-qt-zlib -qt-gif-qt-libpng -qt-libmng -qt-libjpeg 是更好确定Qt编译出的程序能在目前不知的系统下运行。
参数-nomake demos-nomake examples 指的是不编译demos和examples
参数-qt-sql-sqlite 如果没有这个参数，configure的时候，可能会提示sqlite 有问题而中止。
参数 -prefix/usr/local/Trolltech/Qt-5.5.1_static 指明静态编译的Qt安装的目录，命名Qt-5.5.1_static是为了区别动态编译安装的Qt，因为如果没有这个参数，安装时会覆盖之前动态编译安装的Qt（如果有的话）。
u  注:  如果出现错误：Basic XLibfunctionality test failed!
You might need to modify theinclude and library search paths by editing
QMAKE_INCDIR_X11 andQMAKE_LIBDIR_X11
解决办法：yum installlibX*  
（如果是Ubuntu也可运行sudo apt-getinstall libx11-dev libxext-dev libxtst-dev)

> 4、没问题后 make
 
> 5、make没问题后再 sudo make install
 
> 6、增加（或改变）环境变量： （也可以不添加环境变量，使用绝对路径进行编译），在你home目录下你的的名字的目录中,在.profile文件中追加（或改变）如下环境变量：(为Qt设置一些特定的环境变量，这个很重要！.profile文件是隐藏的，可在你的名字目录下，按Ctrl+H显示所有文件查看到)
QTDIR=/usr/local/Trolltech/Qt-5.5.1_static/   
PATH=$QTDIR/bin:$PATH 
MANPATH=$QTDIR/doc/man:$MANPATH   
LD_LIBRARY_PATH=$QTDIR/lib:$LD_LIBRARY_PATH
export QTDIR PATHMANPATH LD_LIBRARY_PATH  

> 7、重启

> 8、在终端测试一下qmake </p>
 
- #### MAC OS X系统平台静态编译
- <p>在MAC OS X系统平台下静态编译QT应用还是比较麻烦的，首先需要静态编译QT应用依赖的各个库，然后再进行连接生成运行文件，具体步骤参看链接：http://doc.qt.io/qt-5/osx-deployment.html。</p>
 
#### 附加Dll文件
- l  优点，更新方便，发布多个产品时，可以统一使用一个库。
- l  缺点，文件多、杂。
- Qt官方开发环境默认使用动态链接库方式，在发布生成的可执行程序时，我们需要复制一大堆动态库，如果自己去复制动态库，很可能丢三落四，导致程序在别的电脑里无法正常运行。 因此 Qt 官方开发环境里自带了一个部署工具来帮助开发者自动拷贝大部分的依赖库。在不同的平台使用方式也有所不同。
- #### Windows平台
Windows开发环境下windeployqt工具 (如果你已经将Qt的bin目录加入PATH环境,那么你可以直接在命令行使用windeployqt调用.)。首先，将项目中的release文件中的可执行文件拷到一个新建的文件夹中，例如project.exe，用Qt自带的生成必备的dll文件的程序windeployqt，来把必要的动态库拷到该文件夹中，打开命令行，输入windeployqtproject.exe，这时候大部分的dll文件都自动拷贝过来了，但是如果项目还用了一些其他的SDK，比如OpenCV，Chartdir51等等，就需要手动将所需dll拷贝过来，如果不知道还需要哪些软件，可以用Dependency Walker来查看缺少哪些dll文件。
注意：如果发布的应用是Qt Quick Application应用，那么命令行需要加上QML的安装目录。命令中的D:\Qt\Qt5.5.1\qml是qml的安装目录,请换成你自己的qml安装目录!!!!!

windeployqt hello.exe--qmldir D:\Qt\Qt5.5.1\qml
接下来要高大上的朋友就可以用Enigma VirtualBox软件虚拟化工具将多个文件封装到应用程序主文件，从而制作成为单执行文件的绿色软件。

- #### linux平台
在X11平台下qt程序，首先准备好程序中需要使用的资源，库和插件...，比如你的可运行程序取名叫作panel，那把你的panel,那些libQt*.so.4和libQt*.so.4.6.0（链接和共享库都要）放在同一目录下(也可以不同,只要小小修改下shell文件).plugins就不多说了。
在程序的同目录下，新建一個空文档，取名panel.sh (文件名与程序名同名,扩展名为sh,shell文件)。在panel.sh中原封不动的写入以下语句:  
> \#!/bin/sh
	appname=`basename $0 | sed s,/.sh$,,`
	  dirname=`dirname$0`
	  tmp="${dirname#?}"
	  if ["${dirname%$tmp}" != "/" ]; then
	   dirname=$PWD/$dirname
	 fi
	   LD_LIBRARY_PATH=$dirname
	export LD_LIBRARY_PATH
	   $dirname/$appname$*
 
保存文件，退出。在终端給文件+x属性: 切换到程序的目录，输入
   chmod +x panel.sh
 
然后运行shell文件就行了（确保panel程序具备X属性）,它会自动更改环境变量,运行程序。
如果要调试shell文件,只需要在终端输入:
   sh -x panel.sh
 
这样就ok了。
如果需要把执行程序制作成DEB或RPM包的话请参考链接：
Deploying aQt5 Application Linux： https://wiki.qt.io/Deploying_a_Qt5_Application_Linux
 
- #### MAC OS X系统平台
由于Qt的库并不是OS X标配的，所以我们要自己去复制库到app包里，才可以让app在其他未安装Qt的电脑上运行。
比较幸运的是，Qt为我们提供了macdeployqt工具，借助于此，在OS X上发布Qt写的程序几乎是所有平台中最简单的。
注：我电脑配置了Qt的bin环境，所以可以直接使用macdeployqt，如果没配置，可以用绝对路径去找。
 
1.发布widgets程序
a)       这个比较方便。选择Release模式，编译
b)       运行macdeployqt
     对于我的工程，命令是：
macdeployqt /Users/Ocean/Desktop/build-untitled-Desktop_5_5_1_64bit-Release/untitled.app-dmg
然后回车，就打包好了。之后我们会发现，app目录下多了一个dmg文件
此dmg文件，里面的app就是我们发布的app了。把dmg拷贝给别人，别人就可以直接使用了。
l  注：如果直接拷贝app文件给别人，别人是无法直接运行的，会有权限问题（要用chmod给可执行文件加上x权限才可以运行）。而压缩过（zip或者dmg）后，拷贝给别人，别人是可以直接运行，没有权限问题。
l  注：-dmg的意思就是在拷贝好库后，生成一个dmg文件，可以不加这个参数。
 
2.发布quick2程序
    这个相对麻烦一点
a)       选择Release模式，编译
b)       打开终端，先切换编译的目标目录下
        对于我的工程，命令是：
           cd /Users/Ocean/Desktop/build-untitled-Desktop_5_5_1_64bit-Release
    
c)       运行macdeployqt
        对于我的工程，命令是：
            macdeployqt untitled.app-qmldir=../untitled -dmg
        然后回车，就打包好了。
l  注1：和widgets发布程序不同，untitled.app 这个名字，要直接输入，不要写 ./untitled.app 或者是其他的 绝对/相对 路径，不然打包出来的文件无法使用！！会报错！！！
l  注2：-qmldir=../untitled的意思就是说在../untitled 目录下有qml文件，让macdeployqt去分析它们，把要用的库找过来。