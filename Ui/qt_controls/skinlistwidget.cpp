#include "skinlistwidget.h"
#include <QBitmap>
#include "skinitem.h"

#define ROWITEMCOUNT 4
#define ROWCOUNT 3
#define ITEMDISTANCE 2
#define PROGRESSBARDISTANCE 20

skinListwidget::skinListwidget(QWidget *parent) :
    QDialog(parent, Qt::Popup)
{
    m_i8UsedCount = 0;
    m_i8TopLine = 10;
    m_i8ButtomLine = m_i8TopLine + 111;
    init();

    QBitmap bitmap(QString(":/controls_res/skinWindowBackground.png"));
    setMask(bitmap);
    setStyleSheet("background: #fff url(:/controls_res/skinWindowforeground.png) top left repeat-x;");
    resize(bitmap.size());
}

void skinListwidget::init()
{
    for (qint8 i8LineIndex = 0; i8LineIndex < ROWCOUNT; ++i8LineIndex)
    {
        for (qint8 iRowIndex = 0; iRowIndex < ROWITEMCOUNT; ++iRowIndex)
        {
            skinItem *pSkinItem = new skinItem(this);
            if (NULL == pSkinItem)
            {
                return;
            }

            pSkinItem->setIndex(i8LineIndex * ROWITEMCOUNT + iRowIndex);
            pSkinItem->show();
            pSkinItem->setEnabled(false);
            connect(pSkinItem, SIGNAL(mouseEnter(qint8,QString)), this, SLOT(mouseEnterItem(qint8,QString)));
            connect(pSkinItem, SIGNAL(mouseLeave(qint8)), this, SLOT(mouseLeaveItem(qint8)));
            connect(pSkinItem, SIGNAL(deleteButtonClicked(qint8,QString)), this, SLOT(deleteButtonClicked(qint8,QString)));
            connect(pSkinItem, SIGNAL(selected(qint8,QString)), this, SLOT(itemSelected(qint8,QString)));
            m_listpSkinItem.push_back(pSkinItem);
        }
    }

    m_listpSkinItem[ROWCOUNT * ROWITEMCOUNT - 1]->setEnabled(true);
    m_listpSkinItem[ROWCOUNT * ROWITEMCOUNT - 1]->setImage(
                ":/controls_res/skinAddNormal.png", ":/controls_res/skinAddMuseOn.png");
    m_listpSkinItem[ROWCOUNT * ROWITEMCOUNT - 1]->setShowDelButton(false);

    m_horizontalSlider.setParent(this);
    m_horizontalSlider.show();
    m_horizontalSlider.setMaximum(100);
    m_horizontalSlider.setMinimum(10);
    m_horizontalSlider.setValue(0);
    m_horizontalSlider.setOrientation(Qt::Horizontal);
    connect(&m_horizontalSlider, SIGNAL(sliderReleased()), this, SIGNAL(horizontalSliderReleased()));
    connect(&m_horizontalSlider, SIGNAL(valueChanged(int)), this, SIGNAL(horizontalSliderValueChanged(int)));

    m_horizontalSlider.setStyleSheet("background: url();");
}

qint8 skinListwidget::calculateItemHeight()
{
    return (m_i8ButtomLine - m_i8TopLine - ITEMDISTANCE * (ROWCOUNT + 1)) / ROWCOUNT;
}

qint8 skinListwidget::calculateItemWidth()
{
    return (width() - ITEMDISTANCE * (ROWITEMCOUNT + 1)) / ROWITEMCOUNT;
}

void skinListwidget::exec(const QPoint &point)
{
    move(point.x() - 145, point.y());
    show();
    QDialog::exec();
}

bool skinListwidget::addImage(const QString &strImagePath, bool bShowDelButton)
{
    if (m_i8UsedCount >= m_listpSkinItem.size() - 1)
    {
        return false;
    }

    m_listpSkinItem[m_i8UsedCount]->setShowDelButton(bShowDelButton);
    m_listpSkinItem[m_i8UsedCount]->setImage(strImagePath);
    m_listpSkinItem[m_i8UsedCount]->setEnabled(true);
    if (0 == m_i8UsedCount)
    {
        setSelectedBkgImg(0);
    }
    m_i8UsedCount++;

    return true;
}

void skinListwidget::reSortImages()
{
    qint8 iItemWidth = calculateItemWidth();
    qint8 iItemHeight = calculateItemHeight();

    // 行
    for (qint8 i8LineIndex = 0; i8LineIndex < ROWCOUNT; ++i8LineIndex)
    {
        //列
        for (qint8 iRowIndex = 0; iRowIndex < ROWITEMCOUNT; ++iRowIndex)
        {
            if (i8LineIndex * ROWITEMCOUNT + iRowIndex >= m_listpSkinItem.size())
            {
                return;
            }

            m_listpSkinItem[i8LineIndex * ROWITEMCOUNT + iRowIndex]->move(
                        iRowIndex * iItemWidth + (iRowIndex + 1) * ITEMDISTANCE,
                        m_i8TopLine + i8LineIndex * iItemHeight + (i8LineIndex + 1) * ITEMDISTANCE);
            m_listpSkinItem[i8LineIndex * ROWITEMCOUNT + iRowIndex]->resize(iItemWidth, iItemHeight);
        }
    }
}

void skinListwidget::resizeEvent(QResizeEvent *event)
{
    QDialog::resizeEvent(event);

    reSortImages();
    m_horizontalSlider.move(PROGRESSBARDISTANCE, m_i8ButtomLine + ITEMDISTANCE * 3);
    m_horizontalSlider.resize(width() - PROGRESSBARDISTANCE * 2, 20);
}

void skinListwidget::mouseEnterItem(qint8 i8Index, const QString &strImagePath)
{
    if (i8Index != m_listpSkinItem.size() - 1)
    {
        emit sgn_mouseEnterItem(i8Index, strImagePath);
    }
}

void skinListwidget::mouseLeaveItem(qint8 i8Index)
{
    if (i8Index != m_listpSkinItem.size() - 1)
    {
        emit sgn_mouseLeaveItem(i8Index);
    }
}

void skinListwidget::deleteButtonClicked(qint8 i8Index, const QString &strImagePath)
{
    emit sgn_deleteButtonClicked(i8Index, strImagePath);

    deleteItem(i8Index);
}

void skinListwidget::deleteItem(qint8 i8DeleteIndex)
{
    if (i8DeleteIndex < 0 || i8DeleteIndex >= m_i8UsedCount)
    {
        return;
    }

    for (; i8DeleteIndex < m_i8UsedCount - 1; ++i8DeleteIndex)
    {
        m_listpSkinItem[i8DeleteIndex]->setImage(m_listpSkinItem[i8DeleteIndex + 1]->getImagePath());
        m_listpSkinItem[i8DeleteIndex]->setSelected(m_listpSkinItem[i8DeleteIndex + 1]->isSelected());
        m_listpSkinItem[i8DeleteIndex]->setShowDelButton(m_listpSkinItem[i8DeleteIndex + 1]->getShowDelButton());
    }
    m_listpSkinItem[i8DeleteIndex]->setEnabled(false);
    m_i8UsedCount--;
}

void skinListwidget::itemSelected(qint8 i8SelectedIndex, const QString &strImagePath)
{
    if (i8SelectedIndex == m_listpSkinItem.size() - 1)
    {
        emit sgn_addSkinButtonClicked();
    }
    else
    {
        if (!m_listpSkinItem[i8SelectedIndex]->isSelected())
        {
            emit sgn_itemSelectChanged(i8SelectedIndex, strImagePath);
        }
    }

    accept();
}

void skinListwidget::setProgressBarValue(int iValue)
{
    m_horizontalSlider.setValue(iValue);
}

void skinListwidget::resize(const QSize &size)
{
    QDialog::resize(size);
}

void skinListwidget::resize(int iWidth, int iHeight)
{
    QDialog::resize(iWidth, iHeight);
}

void skinListwidget::setSelectedBkgImg(int iIndex)
{
    for (int i = 0; i < m_i8UsedCount; ++i)
    {
        if (i == iIndex)
        {
            m_listpSkinItem[i]->setSelected(true);
        }
        else
        {
            m_listpSkinItem[i]->setSelected(false);
        }
    }
}

qint8 skinListwidget::getSelectedBkgIndex()
{
    for (qint8 i8Index = 0; i8Index < m_i8UsedCount; ++i8Index)
    {
        if (m_listpSkinItem[i8Index]->isSelected())
        {
            return i8Index;
        }
    }

    return -1;
}

qint8 skinListwidget::getProgressBarValue()
{
    return m_horizontalSlider.value();
}
