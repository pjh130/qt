#include "imageex.h"

ImageEx::ImageEx()
{

}

ImageEx::~ImageEx()
{

}

//this can create a new image file and return a new file path
bool ImageEx::toGrayImge(const QString &strSrcPath, QString &strDesPath, bool bOverwrite)
{
    //如果是不覆盖，文件原来存在就直接报错
    if (!bOverwrite && QFileInfo::exists(strDesPath))
    {
        return false;
    }

    if(strSrcPath.isEmpty() || !QFileInfo::exists(strSrcPath))
    {
        return false;
    }

    QImage image(strSrcPath);
    int w = image.width();
    int h = image.height();
    QImage iGray(w, h, QImage::Format_RGB32);
    for(int i=0; i<w; i++)
    {
        for(int j=0; j<h; j++)
        {
            QRgb pixel = image.pixel(i,j);
            int gray = qGray(pixel);
            QRgb graypixel = qRgb(gray,gray,gray);
            iGray.setPixel(i, j, graypixel);
        }
    }

    //如果目录不存在需要创建
    QFileInfo info(strDesPath);
    QDir dir(info.absoluteDir());
    if (!dir.exists())
    {
        dir.mkdir(info.absoluteDir().path());
    }

    return iGray.save(strDesPath);
}
