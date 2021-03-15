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

//bool NoFrameDialog::event(QEvent *event)
//{
//    qDebug()<<"NoFrameDialog::event:"<<event->type();
//    return QWidget::event(event);
//}

void NoFrameDialog::mousePressEvent(QMouseEvent *event)
{
    if (event->buttons() == Qt::LeftButton) {
        last_point_ = pos();
        last_position_ = event->globalPos();
        mouse_press_region_ = GetMouseRegion(event->pos().x(), event->pos().y());

        m_bMousePress = true;
    }
    QDialog::mousePressEvent(event);
}

void NoFrameDialog::mouseReleaseEvent(QMouseEvent *event)
{
    //鼠标复原
    setCursor(Qt::ArrowCursor);
    m_bMousePress = false;

    QDialog::mouseReleaseEvent(event);
}

void NoFrameDialog::mouseMoveEvent(QMouseEvent *event)
{
    SetMouseCursor(event->pos().x(), event->pos().y());

    if (m_bMousePress && m_bMoveAble)
    {
        if(event->buttons()==Qt::LeftButton)
        {
            QPoint point_offset = event->globalPos() - last_position_;
            //在合理范围内就可移动窗体
            if(mouse_press_region_ == kMousePositionMid)
            {
                //this->move(event->globalPos() - m_dPos);
                setCursor(Qt::ArrowCursor);
                move(point_offset + last_point_);
            } else {
                QRect rect = geometry();
                switch (mouse_press_region_)
                {
                case kMousePositionLeftTop:
                    rect.setTopLeft(rect.topLeft() + point_offset);
                    break;
                case kMousePositionTop:
                    rect.setTop(rect.top() + point_offset.y());
                    break;
                case kMousePositionRightTop:
                    rect.setTopRight(rect.topRight() + point_offset);
                    break;
                case kMousePositionRight:
                    rect.setRight(rect.right() + point_offset.x());
                    break;
                case kMousePositionRightButtom:
                    rect.setBottomRight(rect.bottomRight() + point_offset);
                    break;
                case kMousePositionButtom:
                    rect.setBottom(rect.bottom() + point_offset.y());
                    break;
                case kMousePositionLeftButtom:
                    rect.setBottomLeft(rect.bottomLeft() + point_offset);
                    break;
                case kMousePositionLeft:
                    rect.setLeft(rect.left() + point_offset.x());
                    break;
                default:
                    qDebug()<<"mouse_press_region_ error:"<<mouse_press_region_;
                    return;
                    break;
                }
                if(rect.isValid() && rect.width() > (kMouseRegionLeft + kMouseRegionRight)
                        && rect.height() > (kMouseRegionTop + kMouseRegionButtom))
                {
                    setGeometry(rect);
                    last_position_ = event->globalPos();
                }
            }
        }
    }

    QDialog::mouseMoveEvent(event);
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

int NoFrameDialog::GetMouseRegionNew(int x, int y)
{
//    qDebug()<<"x:"<<x<<" width:"<<width()<<" y:"<<y<<"height: "<<height();
    if(x > width() || y > height())
    {
//        qDebug()<<"-1";
        return -1;
    }

    //左下角
    if (x <= kMouseRegionLeft && (height() - y) <= kMouseRegionButtom)
    {
//        qDebug()<<"kMousePositionLeftButtom";
        return kMousePositionLeftButtom;
    }

    //左上角
    if (x <= kMouseRegionLeft && y <= kMouseRegionTop)
    {
//        qDebug()<<"kMousePositionLeftTop";
        return kMousePositionLeftTop;
    }

    //右下角
    if ((height() - y) <= kMouseRegionButtom && (width() - x) <= kMouseRegionRight)
    {
//        qDebug()<<"kMousePositionRightButtom";
        return kMousePositionRightButtom;
    }

    //右上角
    if ((width() - x) <= kMouseRegionRight && y <= kMouseRegionTop)
    {
//        qDebug()<<"kMousePositionRightTop";
        return kMousePositionRightTop;
    }

    //左边
    if (x < kMouseRegionLeft)
    {
//        qDebug()<<"kMousePositionLeft";
        return kMousePositionLeft;
    }

    //右边
    if ((width() - x) <= kMouseRegionRight)
    {
//        qDebug()<<"kMousePositionRight";
        return kMousePositionRight;
    }

    //上边
    if (y < kMouseRegionTop)
    {
//        qDebug()<<"kMousePositionTop";
        return kMousePositionTop;
    }

    //下边
    if ((height() - y) <= kMouseRegionButtom)
    {
//        qDebug()<<"kMousePositionButtom";
        return kMousePositionButtom;
    }

    return kMousePositionMid;
}

int NoFrameDialog::GetMouseRegion(int x, int y)
{
    return GetMouseRegionNew(x, y);

    int region_x = 0, region_y = 0;
    if (x < kMouseRegionLeft)
    {
        region_x = 1;
    }
    else if (x > (width() - kMouseRegionRight))
    {
        region_x = 3;
    }
    else
    {
        region_x = 2;
    }
    if (y < kMouseRegionTop)
    {
        region_y = 1;
    }
    else if (y > (height() - kMouseRegionButtom))
    {
        region_y = 3;
    }
    else
    {
        region_y = 2;
    }

    return region_y * 10 + region_x;
}

void NoFrameDialog::SetMouseCursor(int x, int y)
{
    Qt::CursorShape cursor;
    int region = GetMouseRegion(x, y);
    switch (region)
    {
    case kMousePositionLeftTop:
    case kMousePositionRightButtom:
        cursor = Qt::SizeFDiagCursor; break;
    case kMousePositionRightTop:
    case kMousePositionLeftButtom:
        cursor = Qt::SizeBDiagCursor; break;
    case kMousePositionLeft:
    case kMousePositionRight:
        cursor = Qt::SizeHorCursor; break;
    case kMousePositionTop:
    case kMousePositionButtom:
        cursor = Qt::SizeVerCursor; break;
    case kMousePositionMid:
        cursor = Qt::ArrowCursor; break;
    default:
        cursor = Qt::ArrowCursor;
        break;
    }
    setCursor(cursor);
}
