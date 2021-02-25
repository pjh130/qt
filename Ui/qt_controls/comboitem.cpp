#include "comboitem.h"
#include <QPainter>

comboItem::comboItem(QWidget *parent) :
    QWidget(parent)
{
    setAutoFillBackground(true);

    m_EnableMouseEnterEvent = true;
}

void comboItem::mouseReleaseEvent(QMouseEvent *e)
{
    QWidget::mouseReleaseEvent(e);
    emit currentSelect( this );
}

void comboItem::enterEvent(QEvent *event)
{
    QWidget::enterEvent(event);

    if (m_EnableMouseEnterEvent)
    {
        emit mouseEnter(this);
    }
}

void comboItem::paintEvent(QPaintEvent *e)
{
    if (m_colorBackground.isValid())
    {
        QPainter painter(this);
        QPixmap pixmap(width(), height());
        pixmap.fill(m_colorBackground);
        painter.drawPixmap(1, 1, width() - 2, height() - 2, pixmap);
    }

    QWidget::paintEvent(e);
}

void comboItem::setBackgroundColor(const QColor &color)
{
    m_colorBackground = color;
    update();
}

void comboItem::enableMouseEnterEvent(bool bEnable)
{
    m_EnableMouseEnterEvent = bEnable;
}
