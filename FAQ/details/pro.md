QT中.pro文件
===

#####QT加载静态库的问题和解决(导入C语言静态库,QT的运行时库设定)
* 原因和解决办法：
	<p>1、QT和VS都默认使用MD运行库. 那么QT怎么改为使用MT运行库
		QMAKE_CXXFLAGS_RELEASE = -O2 -MT -GL
		QMAKE_CXXFLAGS_DEBUG = -Zi -MTd </p>
	<p>2、使用纯C代码,编译产生的lib具有浓厚的C色彩,作为lib导出的函数修饰符仅仅只有前缀，而我们用c++
	代码加载时,修饰后找的函数却是?我们只找相关的函数(就是报无法解析的外部符号的函数)在前面加
	extern "C"让他按C方式修饰再找,就能找到了. 为了保持原代码的完整性,可以复制xxx.h到xxx_cpp.h,
	在新文件中修改,自己的代码只包含"xxx_cpp.h"</p>
		#ifdef __cplusplus
			extern "C" {
		#endif
		
		#include "xxx.h"
		
		#ifdef __cplusplus
		}
		#endif
		
#####添加LIB
* 方法
	<p>1、LIBS += -L folderPath //引入的lib文件的路径 -L：引入路径</p>
	<p>2、LIBS += -lLibName //引入lib 文件 -l : 引入库名</p>
	
#####应用程序的资源文件(编译出来的程序信息，比如图标，等)
* 方法
	<p>1、新建一个xxx.rc</p>
	<p>2、在.pro文件中添加 RC_FILE = xxx.rc</p>


#####win7下权限提示（UAC）问题
* 方法
	<p>在.pro文件中添加QMAKE_LFLAGS += /MANIFESTUAC:"level='requireAdministrator' uiAccess='false'"即可</p>