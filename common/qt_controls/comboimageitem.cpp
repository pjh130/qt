#include "comboimageitem.h"
#include <QPainter>

#define MIN(x,y) ((x) <= (y) ? (x) : (y))

comboImageItem::comboImageItem(QWidget *parent) : comboItem(parent)
{
    setAutoFillBackground(true);
}

void comboImageItem::setImage(const QImage &image)
{
    m_image = image;
    scaledImage();

    update();
}

void comboImageItem::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.drawImage((width() - m_image.width()) / 2, (height() - m_image.height()) / 2, m_image);

    comboItem::paintEvent(event);
}

void comboImageItem::resizeEvent(QResizeEvent *event)
{
    comboItem::resizeEvent(event);
    scaledImage();
}

const QImage &comboImageItem::getImage() const
{
    return m_image;
}

void comboImageItem::scaledImage()
{
    qint32 iWidth = MIN(width(), height());
    m_image = m_image.scaled(iWidth, iWidth);
}
