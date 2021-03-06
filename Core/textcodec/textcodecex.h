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
    static QByteArray fromUnicode(const QString &strFrom, const QByteArray &byCodeType);
    static QString toUnicode(const QByteArray &byFrom, const QByteArray &byCodeType);
};

#endif // TEXTCODECEX_H
