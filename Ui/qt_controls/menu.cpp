#include "menu.h"
#include <QPainter>
#include <QApplication>
#include <QBitmap>
#include <QPaintEvent>

menu::menu(QWidget *parent) :
    QDialog(parent)
{
    m_menuTrigered = -1;
    m_mouseCurrentIn = -1;
    setMouseTracking(true);
    setWindowFlags(Qt::Popup);
    reSizeMenu();
}

void menu::reSizeMenu()
{
    QImage imageHeader(":/controls_res/menu_header_black.png");
    QImage imageButtom(":/controls_res/menu_buttom_black.png");
    QImage imageBody(":/controls_res/menu_body_black.png");

    QPixmap pixmap(imageHeader.width(), imageHeader.height()
                   + (m_listItem.size() - 1) * imageBody.height() + imageButtom.height());

    QPainter p;

    p.begin(&pixmap);
    p.drawImage(0, 0, imageHeader);

    int iHeight = imageHeader.height();

    for (int iIndex = 0; iIndex < m_listItem.size() - 1; ++iIndex)
    {
        p.drawImage(0, iHeight, imageBody);
        iHeight += imageBody.height();
    }
    p.drawImage(0, iHeight, imageButtom);
    p.end();

    resize(pixmap.size());
    setMask(pixmap);
}

void menu::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);

    QImage imageHeader(":/controls_res/menu_header.png");
    if (0 == m_mouseCurrentIn)
    {
        imageHeader.load(":/controls_res/menu_header_selected.png");
    }
    painter.drawImage(0, 0, imageHeader);

    QImage imageBody(":/controls_res/menu_body.png");
    int iHeight = imageHeader.height();
    for (int iIndex = 0; iIndex < m_listItem.size() - 1; ++iIndex)
    {
        if (m_mouseCurrentIn == iIndex)
        {
            imageBody.load(":/controls_res/menu_body_selected.png");
        }
        else
        {
            imageBody.load(":/controls_res/menu_body.png");
        }
        painter.drawImage(0, iHeight, imageBody);

        QImage image = m_listItem[iIndex].first;
        if (!image.isNull())
        {
            painter.drawImage(45, iHeight + 2,
                image.scaled(imageBody.height() - 15, imageBody.height() - 15));
        }
        painter.drawText(15 + imageBody.height() + 30, iHeight + 15, m_listItem[iIndex].second);

        iHeight += imageBody.height();
    }

    QImage imageButtom(":/controls_res/menu_buttom.png");
    if (m_mouseCurrentIn == m_listItem.size() - 1)
    {
        imageButtom.load(":/controls_res/menu_buttom_selected.png");
    }
    painter.drawImage(0, iHeight, imageButtom);

    if (!m_listItem.isEmpty())
    {
        int iIndex = m_listItem.size() - 1;
        QImage image = m_listItem[iIndex].first;

        if (!image.isNull())
        {
            painter.drawImage(45, iHeight + 2,
               image.scaled(imageBody.height() - 15, imageBody.height() - 15));
        }
        painter.drawText(15 + imageBody.height() + 30, iHeight + 15, m_listItem[iIndex].second);
    }

    QDialog::paintEvent(event);
}

Action menu::addAction(const QImage &image, const QString &text)
{
    m_listItem.push_back(qMakePair(image, text));
    reSizeMenu();
    return m_listItem.size() - 1;
}

Action menu::addAction(const QString &text)
{
    return addAction(QImage(), text);
}

int menu::exec()
{
    return exec(QCursor::pos());
}

int menu::exec(const QPoint &point)
{
    m_menuTrigered = NULL;

    move(point.x() - 235, point.y());

    QDialog::show();
    QDialog::exec();

    return m_menuTrigered;
}

void menu::mousePressEvent(QMouseEvent *event)
{
    QDialog::mousePressEvent(event);

    Action action = isInItemRect(mapTo(this, event->pos()));

    if (action >= 0)
    {
        m_menuTrigered = action;
        accept();
    }
}

Action menu::isInItemRect(const QPoint &point)
{
    QImage imageHeader(":/controls_res/menu_header.png");
    QImage imageBody(":/controls_res/menu_body.png");

    if (QRect(0, imageHeader.height(), imageHeader.width(),
        imageBody.height() * m_listItem.size()).contains(point))
    {
        return (point.y() - imageHeader.height()) / imageBody.height();
    }

    return -1;
}

void menu::mouseMoveEvent(QMouseEvent *event)
{
    QDialog::mouseMoveEvent(event);

    Action action = isInItemRect(mapTo(this, event->pos()));
    if (action != m_mouseCurrentIn)
    {
        m_mouseCurrentIn = action;
        update();
    }
}

void menu::leaveEvent(QEvent *event)
{
    QDialog::leaveEvent(event);

    m_mouseCurrentIn = -1;
    update();
}
