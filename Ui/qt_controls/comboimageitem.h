#ifndef COMBOIMAGEITEM_H
#define COMBOIMAGEITEM_H

#include "comboitem.h"
#include <QIcon>

class comboImageItem : public comboItem
{
public:
    comboImageItem(QWidget *parent = 0);

    void setImage(const QImage &image);
    const QImage &getImage() const;

private:
    void paintEvent(QPaintEvent *);
    void resizeEvent(QResizeEvent *);
    void scaledImage();

private:
    QImage m_image;
};

#endif // COMBOIMAGEITEM_H
