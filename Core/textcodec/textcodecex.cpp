#include "textcodecex.h"

TextCodecEx::TextCodecEx()
{

}

TextCodecEx::~TextCodecEx()
{

}

void TextCodecEx::setCodecForLocale()
{
#if (QT_VERSION <= QT_VERSION_CHECK(5,0,0))
#if _MSC_VER
    QTextCodec *codec = QTextCodec::codecForName("GBK");
#else
    QTextCodec *codec = QTextCodec::codecForName("UTF-8");
#endif
    QTextCodec::setCodecForLocale(codec);
    QTextCodec::setCodecForCStrings(codec);
    QTextCodec::setCodecForTr(codec);
#else
    QTextCodec *codec = QTextCodec::codecForName("UTF-8");
    QTextCodec::setCodecForLocale(codec);
#endif

}

QByteArray TextCodecEx::fromUnicode(const QString &strFrom, const QByteArray &byCodeType)
{
    QTextCodec *codec = QTextCodec::codecForName(byCodeType);
    return codec->fromUnicode(strFrom);
}

QString TextCodecEx::toUnicode(const QByteArray &byFrom, const QByteArray &byCodeType)
{
    QTextCodec *codec = QTextCodec::codecForName(byCodeType);
    return codec->toUnicode(byFrom);
}
