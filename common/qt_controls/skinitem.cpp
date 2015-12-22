#include "skinitem.h"
#include <QPainter>
#include <QVector>
#include <QEvent>
#include <QRect>
#include <QMouseEvent>
#include <QPixmap>

skinItem::skinItem(QWidget *parent) :
    QWidget(parent)
{
    m_bSelected = false;
    m_bMouseOn = false;

    m_imageDelete.load(":/controls_res/skinwindowdelete.png");
    m_imageDelete = m_imageDelete.scaled(15, 15);

    m_i8Index = -1;
}

void skinItem::rePlaceDelButton()
{
    m_pointDeleteButton.setX(width() - m_imageDelete.width());
    m_pointDeleteButton.setY(0);
}

void skinItem::setImage(const QString &strImagePath)
{
    m_imageNormal.load(strImagePath);
    m_strImagePath = strImagePath;
}

void skinItem::setShowDelButton(bool bShow)
{
    m_bShowDelButton = bShow;
    update();
}

bool skinItem::getShowDelButton()
{
    return m_bShowDelButton;
}

void skinItem::setIndex(qint8 iIndex)
{
    m_i8Index = iIndex;
}

void skinItem::setImage(const QString &strNormalImagePath, const QString &strMouseOnImagePath)
{
    m_imageNormal.load(strNormalImagePath);
    m_imageMouseOn.load(strMouseOnImagePath);
}

void skinItem::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);

    if (isEnabled())
    {
        if (m_bMouseOn && !m_imageMouseOn.isNull())
        {
            painter.drawImage(0, 0, m_imageMouseOn.scaled(size()));
        }
        else if (m_bMouseOn || m_bSelected)
        {
            if (!m_imageNormal.isNull())
            {
                painter.drawImage(0, 0, m_imageNormal.scaled(size()));
            }

            QImage pixmap(":/controls_res/PicSelected.png");
            painter.drawImage(0, 0, pixmap.scaled(size()));
        }
        else
        {
            if (!m_imageNormal.isNull())
            {
                painter.drawImage(0, 0, m_imageNormal.scaled(size()));
            }
        }

        if (m_bMouseOn && m_bShowDelButton)
        {
            painter.drawImage(m_pointDeleteButton, m_imageDelete);
        }
    }
    else
    {
        QPixmap pixmapDistance(size());
        pixmapDistance.fill(Qt::gray);
        painter.drawPixmap(0, 0, pixmapDistance);
    }

    QWidget::paintEvent(event);
}


void skinItem::enterEvent(QEvent *event)
{
    QWidget::enterEvent(event);

    if (isEnabled())
    {
        m_bMouseOn = true;
        update();
        emit mouseEnter(m_i8Index, m_strImagePath);
    }
}

void skinItem::leaveEvent(QEvent *event)
{
    QWidget::leaveEvent(event);

    if (isEnabled())
    {
        m_bMouseOn = false;
        update();
        emit mouseLeave(m_i8Index);
    }
}

void skinItem::resizeEvent(QResizeEvent *event)
{
    QWidget::resizeEvent(event);

    rePlaceDelButton();
}

bool skinItem::event(QEvent *pEvent)
{
    if (isEnabled() && pEvent->type() == QEvent::MouseButtonRelease)
    {
        if (m_bShowDelButton)
        {
            QRect rect(m_pointDeleteButton, QPoint(m_pointDeleteButton.rx() + m_imageDelete.width(),
                 m_pointDeleteButton.ry() + m_imageDelete.height()));
            if (rect.contains(((QMouseEvent*)pEvent)->pos()))
            {
                emit deleteButtonClicked(m_i8Index, m_strImagePath);
            }
            else
            {
                emit selected(m_i8Index, m_strImagePath);
            }
        }
        else
        {
            emit selected(m_i8Index, m_strImagePath);
        }
    }

    return QWidget::event(pEvent);
}

bool skinItem::isSelected()
{
    return m_bSelected;
}

void skinItem::setSelected(bool bSelected)
{
    m_bSelected = bSelected;
    update();
}

QString skinItem::getImagePath()
{
    return m_strImagePath;
}
