#ifndef TEXTCODECEX_H
#define TEXTCODECEX_H
#include <QtCore>
#include <QTextCodec>

class TextCodecEx
{
public:
    TextCodecEx();
    ~TextCodecEx();

    //设置字符集
    static void setCodecForLocale();
};

#endif // TEXTCODECEX_H
