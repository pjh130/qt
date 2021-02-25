#include "searchBoxMenu.h"
#include "searchMenuExtendItem.h"

searchBoxMenu::searchBoxMenu(QWidget *parent, Qt::WindowFlags f)
    : comboItemList (parent, f)
{
}

void searchBoxMenu::setData(const QList<searchboxData> &listData)
{
    QList<comboItem*> listItem;

    for (QList<searchboxData>::const_iterator iter = listData.begin(); iter != listData.end();)
    {
        searchMenuItem *pSearchBoxItem = new searchMenuItem;
        if (NULL == pSearchBoxItem)
        {
            continue;
        }

        pSearchBoxItem->setInfo(iter->pixmap, iter->strText);
        listItem.push_back(pSearchBoxItem);
        ++iter;
    }

    setItem(listItem);
}

void searchBoxMenu::setExternItemData(const QList<searchExtendItemData> &listData)
{
    QList<comboItem*> listItem;

    for (QList<searchExtendItemData>::const_iterator iter = listData.begin(); iter != listData.end();)
    {
        searchMenuExtendItem *pSearchExtendItem = new searchMenuExtendItem;
        if (NULL == pSearchExtendItem)
        {
            continue;
        }

        pSearchExtendItem->setInfo(iter->pixmap, iter->strText);
        listItem.push_back(pSearchExtendItem);
        ++iter;
    }

    setExtendItem(listItem);
}
