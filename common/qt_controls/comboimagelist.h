#ifndef COMBOIMAGELIST_H
#define COMBOIMAGELIST_H

#include "comboitemlist.h"

class comboImageList : public comboItemList
{
public:
    comboImageList(QWidget *parent = 0, Qt::WindowFlags f = 0);

    void setData(const QList<QImage> &listImage);
    QImage getItemImage(qint8 iIndex);
};

#endif // COMBOIMAGELIST_H
