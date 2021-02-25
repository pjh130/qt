#include "comboimagelist.h"
#include "comboimageitem.h"

comboImageList::comboImageList(QWidget *parent, Qt::WindowFlags f)
    : comboItemList(parent, f)
{

}

void comboImageList::setData(const QList<QImage> &listImage)
{
    QList<comboItem*> listItem;

    for (QList<QImage>::const_iterator iter = listImage.begin(); iter != listImage.end(); ++iter)
    {
        comboImageItem *pItem = new comboImageItem;
        pItem->setImage(*iter);
        listItem.push_back(pItem);
    }

    setItem(listItem);
}

QImage comboImageList::getItemImage(qint8 iIndex)
{
    if (iIndex >= m_lstWidgetItem.size() || iIndex < 0)
    {
        return QImage();
    }

    return ((comboImageItem*)m_lstWidgetItem[iIndex])->getImage();
}
