#ifndef STRINGEX_H
#define STRINGEX_H
#include <QtCore>

class StringEx
{
public:
    StringEx();
    ~StringEx();

    /// @brief 截取字符串的首部分
    /// @param [in,out] str 被截取的字符串
    /// @param [in] split 字符串的分隔符
    /// @return 截取出的字符串
    /// @note 分隔符将被丢弃，不含分隔符时截取整个字符串，被截取的字符串将被修改
    static QByteArray   first(QByteArray &str, const QByteArray &split="\t");
};

#endif // STRINGEX_H
