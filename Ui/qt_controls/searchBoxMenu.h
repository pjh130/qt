#ifndef SEARCHBOXMENU_H
#define SEARCHBOXMENU_H

#include <QPixmap>
#include <QVariant>
#include "searchMenuItem.h"
#include "comboitemlist.h"

typedef struct
{
    QPixmap pixmap;
    QString strText;
    QVariant data;
}searchboxData;

typedef struct
{
    QPixmap pixmap;
    QString strText;
    QVariant data;
}searchExtendItemData;

class searchBoxMenu : public comboItemList
{
public:
    searchBoxMenu(QWidget *parent = 0, Qt::WindowFlags f = 0);

    void setData(const QList<searchboxData> &listData);
    void setExternItemData(const QList<searchExtendItemData> &listData);
};

#endif // SEARCHBOXMENU_H
