#include "noframeDialog.h"
#include <QPainter>
#include <QBitmap>
#include <QApplication>

NoFrameDialog::NoFrameDialog(QWidget *parent/* = 0*/, Qt::WindowFlags f/* = 0*/)
    : QDialog(parent, f)
{
    setWindowFlags(Qt::FramelessWindowHint);

    m_bMousePress = false;
    m_bMoveAble = true;
}

void NoFrameDialog::mousePressEvent(QMouseEvent *event)
{
    QDialog::mousePressEvent(event);

    this->m_WindowPos = this->pos();
    this->m_MousePos = event->globalPos();
    this->m_dPos = m_MousePos - m_WindowPos;

    m_bMousePress = true;
}

void NoFrameDialog::setVisible(bool bVisible)
{
    if (!bVisible && !isHidden())
    {
        emit windowHidden();
    }

    QDialog::setVisible(bVisible);
}

void NoFrameDialog::setMoveAble(bool bMoveAble)
{
    m_bMoveAble = bMoveAble;
}

void NoFrameDialog::mouseMoveEvent(QMouseEvent *event)
{
    if (m_bMousePress && m_bMoveAble)
    {
        if(event->buttons()==Qt::LeftButton)
        {
            this->move(event->globalPos() - this->m_dPos);
        }
    }

    QDialog::mouseMoveEvent(event);
}

void NoFrameDialog::mouseReleaseEvent(QMouseEvent *event)
{
    QDialog::mouseReleaseEvent(event);

    m_bMousePress = false;
}

void NoFrameDialog::focusOutEvent(QFocusEvent *ev)
{
    QDialog::focusOutEvent(ev);

    m_bMousePress = false;
}

void NoFrameDialog::leaveEvent(QEvent *ev)
{
    QDialog::leaveEvent(ev);

    m_bMousePress = false;
}

void NoFrameDialog::resizeEvent(QResizeEvent *event)
{
    QDialog::resizeEvent(event);

    QBitmap bmp(size());
    bmp.fill();
    QPainter p(&bmp);
    p.setRenderHint(QPainter::Antialiasing);
    p.setPen(Qt::NoPen);
    p.setBrush(Qt::black);
    p.drawRoundedRect(bmp.rect(), 3, 3);

    setMask(bmp.scaled(size()));

    emit sizeChanged(size());
}

void NoFrameDialog::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Escape)
    {
        event->ignore();
        return;
    }

    QDialog::keyPressEvent(event);
}
