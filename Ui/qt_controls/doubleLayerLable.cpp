#include "doubleLayerLable.h"
#include <QPainter>
#include <QPaintEvent>

doubleLayerLable::doubleLayerLable(QWidget *parent) :
    QLabel(parent), m_colorfront(255,255,255), m_colorBack(0,0,0)
{
    m_i8XDistance = 1;
    m_i8YDistance = 1;
}

void doubleLayerLable::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.setPen(m_colorBack);
    painter.drawText(m_i8XDistance, m_i8YDistance, width(), height(), alignment(), text());
    painter.setPen(m_colorfront);
    painter.drawText(0, 0, width(), height(), alignment(), text());

    event->ignore();
}

void doubleLayerLable::setDistance(qint8 i8XDistance, qint8 iYDistance)
{
    m_i8XDistance = i8XDistance;
    m_i8YDistance = iYDistance;

    update();
}

void doubleLayerLable::setColor(QColor colorfront, QColor colorBack)
{
    m_colorfront = colorfront;
    m_colorBack = colorBack;

    update();
}
