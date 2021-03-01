#ifndef IMAGEEX_H
#define IMAGEEX_H
#include <QtCore>
#include <QFileInfo>
#include <QImage>

class ImageEx
{
public:
    ImageEx();
    ~ImageEx();
    //让图片变灰
    static bool toGrayImge(const QString &strSrcPath, QString &strDesPath,
                           bool bOverwrite = true);
};

#endif // IMAGEEX_H
