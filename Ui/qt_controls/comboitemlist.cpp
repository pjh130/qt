#include "comboitemlist.h"
#include "comboitem.h"
#include <QPainter>
#include <QKeyEvent>

#define ROLLBARWIDTH 8

comboItemList::comboItemList(QWidget *parent, Qt::WindowFlags f) :
    QDialog(parent, f), m_scrollBar(this)
{
    connect(this, SIGNAL(selectChanged(int)), this, SLOT(accept()));
    connect(&m_scrollBar, SIGNAL(valueChanged(int)), this, SLOT(scrollValueChange(int)));

    m_iActiveIndex = 0;
    m_iMaxShowItem = 10;
    m_iFirstShowIndex = 0;

    m_iNormalHeight = 30;
    m_iActiveHeight = 40;

    m_colorItemActive = QColor(203, 241, 255);
    m_colorItemNormal = QColor(255, 255, 255);

    m_iExtendItemHeight = 25;
}

comboItemList::~comboItemList()
{
    clearAllExtendItem();
    clearAllItem();
}

void comboItemList::setItemHeight(int iNormalHeight, int iActiveHeight)
{
    m_iNormalHeight = iNormalHeight;
    m_iActiveHeight = iActiveHeight;

    reScollwindow();
}

void comboItemList::addItem(const QList<comboItem*> &itemList)
{
    QList<comboItem*> itemListTmp = itemList;
    for (QList<comboItem*>::iterator iter = itemListTmp.begin(); iter != itemListTmp.end();)
    {
        if (NULL == *iter)
        {
            itemListTmp.erase(iter);
            continue;
        }
        (*iter)->setParent(this);
        connect(*iter, SIGNAL(currentSelect(comboItem*)), this, SLOT(itemClicked(comboItem*)));
        connect(*iter, SIGNAL(mouseEnter(comboItem*)), this, SLOT(itemMouseEnter(comboItem*)));
        ++iter;
    }

    if (itemListTmp.isEmpty())
    {
        return;
    }

    bool bNeedResortWindow = false;
    if (m_lstWidgetItem.size() - m_iFirstShowIndex <= m_iMaxShowItem)
    {
        bNeedResortWindow = true;
    }
    m_lstWidgetItem.append(itemListTmp);
    if (bNeedResortWindow)
    {
        reScollwindow();
    }

    reSetScrollBarRange();
}

void comboItemList::addExtendItem(const QList<comboItem*> &itemList)
{
    QList<comboItem*> itemListTmp = itemList;
    for (int iIndex = 0; iIndex < itemListTmp.size();)
    {
        if (NULL == itemListTmp[iIndex])
        {
            itemListTmp.removeAt(iIndex);
            continue;
        }
        connect(itemListTmp[iIndex], SIGNAL(currentSelect(comboItem*)),
                this, SLOT(itemClicked(comboItem*)));
        connect(itemListTmp[iIndex], SIGNAL(mouseEnter(comboItem*)),
                this, SLOT(itemMouseEnter(comboItem*)));
        ++iIndex;
    }

    if (itemListTmp.isEmpty())
    {
        return;
    }
    m_lstExtendItem.append(itemListTmp);

    reScollwindow();
}

void comboItemList::reSetScrollBarRange()
{
    m_scrollBar.setRange(0, m_lstWidgetItem.size() - 1);
}

void comboItemList::setScrollBarValue(int iValue)
{
    m_scrollBar.setValue(iValue);
}

void comboItemList::itemClicked(comboItem *pItem)
{
    if (NULL != pItem)
    {
        for (int iIndex = m_iFirstShowIndex; iIndex < m_iFirstShowIndex + m_iMaxShowItem
             && iIndex < m_lstWidgetItem.size(); ++iIndex)
        {
            if (pItem == m_lstWidgetItem[iIndex])
            {
                emit selectChanged(iIndex);
                return;
            }
        }

        for (int iIndex = 0; iIndex < m_lstExtendItem.size(); ++iIndex)
        {
            if (m_lstExtendItem[iIndex] == pItem)
            {
                emit extendItemClicked(iIndex);
                reject();
                return;
            }
        }
    }
}

void comboItemList::itemMouseEnter(comboItem *pItem)
{
    if (NULL == pItem)
    {
        return;
    }

    for (int iIndex = m_iFirstShowIndex; iIndex < m_iFirstShowIndex + m_iMaxShowItem
         && iIndex < m_lstWidgetItem.size(); ++iIndex)
    {
        if (pItem == m_lstWidgetItem[iIndex])
        {
            m_iActiveIndex = iIndex;
            reHeightItem();
            return;
        }
    }

    for (int iIndex = 0; iIndex < m_lstExtendItem.size(); ++iIndex)
    {
        if (pItem == m_lstExtendItem[iIndex])
        {
            setExtendItemActived(pItem, true);
        }
        else
        {
            setExtendItemActived(pItem, false);
        }
    }
}

void comboItemList::scrollValueChange(int iValue)
{
    if (iValue >= m_iFirstShowIndex && iValue < m_iFirstShowIndex + m_iMaxShowItem)
    {
        m_iActiveIndex = iValue;
        reHeightItem();
    }
    else
    {
        if (iValue < m_iFirstShowIndex)
        {
            m_iActiveIndex = iValue;
            m_iFirstShowIndex = iValue;
        }
        else
        {
            m_iActiveIndex = iValue;
            m_iFirstShowIndex = iValue - m_iMaxShowItem + 1;
        }

        reScollwindow();
    }
}

void comboItemList::clearAllItem()
{
    for (QList<comboItem*>::iterator iter = m_lstWidgetItem.begin();
         iter != m_lstWidgetItem.end(); ++iter)
    {
        (*iter)->deleteLater();
    }
    m_lstWidgetItem.clear();

    m_iActiveIndex = 0;
    m_iFirstShowIndex = 0;
    m_scrollBar.setValue(0);

    reScollwindow();
}

void comboItemList::clearAllExtendItem()
{
    for (QList<comboItem*>::iterator iter = m_lstExtendItem.begin();
         iter != m_lstExtendItem.end(); ++iter)
    {
        (*iter)->deleteLater();
    }
    m_lstExtendItem.clear();
}

void comboItemList::setItem(const QList<comboItem*> &itemList)
{
    clearAllItem();
    addItem(itemList);
}

void comboItemList::setExtendItem(const QList<comboItem*> &itemList)
{
    clearAllExtendItem();
    addExtendItem(itemList);
}

void comboItemList::keyPressEvent(QKeyEvent *ev)
{
    if (ev->key() == Qt::Key_Up)
    {
        m_scrollBar.setValue(m_iActiveIndex - 1);
    }
    else if (ev->key() == Qt::Key_Down)
    {
        m_scrollBar.setValue(m_iActiveIndex + 1);
    }
    else if (ev->key() == Qt::Key_Enter || ev->key() == Qt::Key_Return)
    {
        emit selectChanged(m_iActiveIndex);
    }

    QDialog::keyPressEvent(ev);
}

void comboItemList::setItemActived(comboItem*, bool)
{

}

void comboItemList::setExtendItemActived(comboItem*, bool)
{

}

void comboItemList::resizeEvent(QResizeEvent *ev)
{
    QDialog::resizeEvent(ev);

    emit sizeChanged(ev->size(), ev->oldSize());
}

void comboItemList::deleteItem(int iIndex)
{
    if ((iIndex < 0) || (m_lstWidgetItem.size() <= iIndex))
    {
        return;
    }

    delete m_lstWidgetItem.at(iIndex);
    m_lstWidgetItem.removeAt(iIndex);

    reScollwindow();
    reSetScrollBarRange();
}

void comboItemList::setMaxShowItem(int iMaxShowItem)
{
    if (iMaxShowItem <= 0 || m_iMaxShowItem == iMaxShowItem)
    {
        return;
    }
    m_iMaxShowItem = iMaxShowItem;

    reScollwindow();
}

void comboItemList::setWidth(int iWidth)
{
    resize(iWidth, height());
}

void comboItemList::setItemNormalColor(const QColor &color)
{
    m_colorItemNormal = color;
}

void comboItemList::setItemActiveColor(const QColor &color)
{
    m_colorItemActive = color;
}

void comboItemList::reHeightItem()
{
    int iheight = 0;
    for (int iIndex = m_iFirstShowIndex; iIndex < m_iFirstShowIndex + m_iMaxShowItem
         && iIndex < m_lstWidgetItem.size(); ++iIndex)
    {
        comboItem* pItem = m_lstWidgetItem[iIndex];
        if (NULL != pItem)
        {
            pItem->move(0, iheight);
            if (iIndex != m_iActiveIndex)
            {
                pItem->resize(pItem->width(), m_iNormalHeight);
                iheight += m_iNormalHeight;
                pItem->setBackgroundColor(m_colorItemNormal);

                setItemActived(pItem, false);
            }
            else
            {
                pItem->resize(pItem->width(), m_iActiveHeight);
                iheight += m_iActiveHeight;
                pItem->setBackgroundColor(m_colorItemActive);

                setItemActived(pItem, true);
            }
        }
    }

    for (int iIndex = 0; iIndex < m_lstExtendItem.size(); ++iIndex)
    {
        comboItem* pItem = m_lstExtendItem[iIndex];
        if (NULL != pItem)
        {
            pItem->move(0, iheight);
            iheight += m_iExtendItemHeight;
        }
    }
}

void comboItemList::reScollwindow()
{
    int iExtendItemsHeight = m_iExtendItemHeight * m_lstExtendItem.size();
    int iItemsHeight = 0;
    if (m_iMaxShowItem > m_lstWidgetItem.size())
    {
        if (!m_lstWidgetItem.isEmpty())
        {
            iItemsHeight = (m_lstWidgetItem.size() - 1) * m_iNormalHeight + m_iActiveHeight;
        }
    }
    else
    {
        iItemsHeight = (m_iMaxShowItem - 1) * m_iNormalHeight + m_iActiveHeight;
    }
    resize(width(), iItemsHeight + iExtendItemsHeight);

    if (m_lstWidgetItem.size() > m_iMaxShowItem)
    {
        m_scrollBar.setVisible(true);
        m_scrollBar.move(width() - ROLLBARWIDTH, 0);
        m_scrollBar.resize(ROLLBARWIDTH, iItemsHeight);
    }
    else
    {
        m_scrollBar.setVisible(false);
    }

    for (int iIndex = 0; iIndex < m_lstWidgetItem.size(); ++iIndex)
    {
        comboItem * pItem = m_lstWidgetItem[iIndex];
        if (NULL == pItem)
        {
            continue;
        }

        if (m_lstWidgetItem.size() > m_iMaxShowItem)
        {
            pItem->resize(m_scrollBar.pos().rx(), m_iNormalHeight);
        }
        else
        {
            pItem->resize(width(), m_iNormalHeight);
        }

        if (iIndex >= m_iFirstShowIndex && iIndex < m_iFirstShowIndex + m_iMaxShowItem)
        {
            pItem->setParent(this);
            pItem->show();
        }
        else
        {
            pItem->hide();
            pItem->setParent(NULL);
        }
    }

    for (int iIndex = 0; iIndex < m_lstExtendItem.size(); ++iIndex)
    {
        comboItem * pItem = m_lstExtendItem[iIndex];
        if (NULL == pItem)
        {
            continue;
        }
        pItem->resize(width(), m_iExtendItemHeight);
        pItem->setParent(this);
        pItem->show();
    }

    reHeightItem();
}

