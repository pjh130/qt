#include "comboboxlist.h"

comboboxList::comboboxList(QWidget *parent, Qt::WindowFlags f)
    : comboItemList(parent, f)
{
}

comboboxList::~comboboxList()
{
    clearAllItem();
}

void comboboxList::setData(const QList<comboboxData> &listWidget)
{
    QList<comboItem*> listItem;

    for (QList<comboboxData>::const_iterator iter = listWidget.begin(); iter != listWidget.end();)
    {
        comboBoxItem *pComboBoxItem = new comboBoxItem;
        if (NULL == pComboBoxItem)
        {
            continue;
        }

        pComboBoxItem->setInfo(iter->pixmap, iter->strMainText, iter->strMinorText, iter->bNeedDelButton);
        connect(pComboBoxItem, SIGNAL(buttonClicked(comboBoxItem *)), this, SLOT(slot_buttonClicked(comboBoxItem *)));
        listItem.push_back(pComboBoxItem);
        ++iter;
    }

    setItem(listItem);
}

void comboboxList::slot_buttonClicked(comboBoxItem *pItem)
{
    if (NULL == pItem)
    {
        return;
    }

    for (int iIndex = 0; iIndex < m_lstWidgetItem.size(); ++iIndex)
    {
        if (pItem == m_lstWidgetItem[iIndex])
        {
            emit buttonClicked(iIndex);
            break;
        }
    }
}

void comboboxList::setItemActived(comboItem* pItem, bool bActive)
{
    if (NULL == pItem)
    {
        return;
    }

    ((comboBoxItem *)pItem)->setShowButton(bActive);
}
