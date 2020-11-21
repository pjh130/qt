JQHttpServer是基于Qt开发的轻量级HTTP/HTTPS服务器

底层有QTcpSocket、QSslSocket两个版本，分别对应HTTP和HTTPS。

用到的Qt库有：
core
network
concurrent
testlib（测试用，运行不需要）
OpenSSL（如果需要HTTPS）
不依赖外部库，理论上可以部署到任何Qt支持的平台上。

推荐使用Linux系统或者Unix系统，因为在5.7后，Qt更换了Unix相关系统的底层模型，从select更换为了poll，这样改进后，并发就脱离了1024个的限制。

使用本库，推荐 Qt5.8.0 或者更高版本，以及支持 C++11 的编译器（例如VS2013或者更高），对操作系统无要求。

本库源码均已开源在了GitHub上。

GitHub地址：https://github.com/188080501/JQHttpServer