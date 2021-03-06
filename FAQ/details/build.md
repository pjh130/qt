####Qt 如何打包一个软件？
- [depends查看DLL依赖](http://www.dependencywalker.com/)
- [如何打包一个软件](https://www.zhihu.com/question/21359230)
- [Qt 程序打包发布总结](http://blog.csdn.net/liuyez123/article/details/50462637)

####为什么 Qt Creator 的编译如此之慢
- <p>1. “用Qt写的程序编译比MFC慢”的说法是错误的
绝对错误，单位代码行数编译Qt远比MFC快得多，因为Qt库的头文件设计非常好，尽量都使用了前置声明，避免了头文件嵌套，几乎所有类都使用了公有类和私有类的设计，把没必要公开的声明放到私有头文件里，避免了编译时引入过多代码。而MFC没有这样的设计。
至于大家感觉MFC快主要原因是MFC工程默认打开了编译预处理头文件（PCH），但是这是VC编译器的特性，所有C++程序都可以用，不是MFC特有，Qt也可以使用 PCH
方法很简单，在你的 .pro 文件中加入一行
PRECOMPILED_HEADER = stable.h
指定 Stable.h这个头文件作为编译预处理文件，MFC里这个文件一般叫stdafx.h
然后在 stable.h里 包含你所用到的所有 Qt 头文件，如果你用了很多qt的类可以直接包含所有
比如 ：
#include <QtCore>
#include <QtGui>
这两个文件里又包含了几乎所有Qt常用类
不用担心，即使包含了所有头文件也没关系，有了PCH再多头文件也没影响。

如果你还想编译再快点，可以在 .pro里加入下面一行
QMAKE_CXXFLAGS += /MP
指定/mp编译选项，编译器将使用并行编译，同时起多个编译进程并行编译不同的cpp

而且QT这种引入PCH的方法比MFC的好，由于MFC的PCH选项是每个工程逐个指定的，很容易被某些人搞坏，我曾经无数次修复PCH问题，但是Qt的选项是写在.pro里的，写一次就永远不会错。
MFC一旦弄坏了PCH，编译也慢得令人发指。

给个参考时间吧，YY最新版本大约 100多万行C++代码，rebuild debug和releae总共需要20多分钟，机器是i5 四核SSD硬盘。其实对于大项目硬盘才是瓶颈，如果换机械硬盘要慢差不多70%，有个同事用10G内存做了个内存盘编译，还能快30%。

如果你比这个慢，请检查自己的代码问题。

2. “QT本身编译慢”的说法是错的
Qt本身其实编译并不慢，慢的是webkit库和例子程序，你如果不改任何选项默认是会编译所有的，webkit本身就是个恐龙级项目，用了太多泛型技术，编译非常慢。另外Qt里附带了数百个例子工程，都编译一边也很慢。如果仅编译QT核心库是很快的，比如QtCore只需要1分钟，QtGui大约5分钟。

送个福利（仅限windows vc＋＋ 2008）：
configure.exe -qt-libjpeg -qt-zlib -qt-libpng -qt-libjpeg -qt-gif -no-libtiff -no-libmng -nomake examples -nomake demos -no-webkit -nomake doc -no-plugin-manifests -no-exceptions -no-rtti -no-qt3support -no-openssl -no-opengl -no-multimedia -no-3dnow -no-native-gestures -no-style-motif -no-style-cde -no-style-cleanlooks -no-style-plastique -no-sql-sqlite -no-dbus -platform win32-msvc2008

这是我自己用的Qt编译前的配置命令行，把我自己用不到的都去掉了，这样配置编译就快很多了。
我把 webkit examples demos 等大家伙都去掉了。如果你真的需要这些，可以安装Qt sdk里面有编译好的版本。

补充：Qt creator只是IDE，不是编译器，编译慢真的不关他的事，要看你具体用的编译器是什么。一般来说在Windows下就是minGW，也就是一个移植版本的GCC，的确是不如VC++里的CL快的。
如果是其它平台，那么编译器可以换成LLVM的clang，那就快很多了。
在Windows下来是用VC++吧，推荐VC2008，Qt和VC的IDE结合非常好，我现在的项目都是用VC2008+QT的，开发效率很高，记得装Visual Assist哦。</p>