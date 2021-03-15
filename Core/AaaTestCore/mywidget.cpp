#include "mywidget.h"

MyWidget::MyWidget(QWidget *parent) : QWidget(parent)
{
//    setWindowFlags(Qt::FramelessWindowHint);
}

MyWidget::~MyWidget()
{

}

bool MyWidget::event(QEvent *event)
{
    qDebug()<<"MyWidget::event:"<<event->type();
    return QWidget::event(event);
}

void MyWidget::mousePressEvent(QMouseEvent *event)
{
    qDebug()<<"MyWidget::mousePressEvent";
    QWidget::mousePressEvent(event);
}
void MyWidget::mouseMoveEvent(QMouseEvent *event)
{
    qDebug()<<"MyWidget::mouseMoveEvent";
    QWidget::mouseMoveEvent(event);
}
void MyWidget::mouseReleaseEvent(QMouseEvent *event)
{
    qDebug()<<"MyWidget::mouseReleaseEvent";
    QWidget::mouseReleaseEvent(event);
}
