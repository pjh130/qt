#include "blurWindow.h"
#include "qtwin.h"
#include <QPainter>

blurWindow::blurWindow(QWidget *parent, Qt::WindowFlags f) : windowFrame(parent, f)
{
    QtWin::blurWidget(this);
    m_realOpacity = 0.8;

    m_bHeaderImageShowHole = false;
    m_bSetFrontColor = false;

    setBackgroudImage(":/res/background.png");
//    setwindowHearImage(":/res/background.png", true);
}

blurWindow::~blurWindow()
{

}

void blurWindow::setBackgroudImage(const QString &strImagePath)
{
    setBackgroudImage(QImage(strImagePath));
}

void blurWindow::setBackgroudImage(const QImage &image)
{
    m_imageBackgroud = image;

    updateImageBuffer(size());

    update();
}

void blurWindow::updateImageBuffer(const QSize &size)
{
    QPixmap pixmap(1, 1);
    pixmap.fill(QColor(255,255,255,0));
    m_imageBuffer = pixmap.toImage().scaled(size);
    QPainter painter(&m_imageBuffer);
    painter.setOpacity(m_realOpacity);

    bool bDrwa = false;
    if (!m_imageBackgroud.isNull())
    {
        painter.drawImage(0, 0, m_imageBackgroud.scaled(size));
        bDrwa = true;
    }

    if (!m_imageHeaderImage.isNull())
    {
        if (m_bHeaderImageShowHole)
        {
            painter.drawImage(0, 0, m_imageHeaderImage.scaled(size));
            bDrwa = true;
        }
        else
        {
            bDrwa = true;
            painter.drawImage(0, 0, m_imageHeaderImage);
        }
    }

    if (m_bSetFrontColor)
    {
        painter.fillRect(rect(), m_colorNormal);

        for (QList<QPair<QRect, QColor> >::iterator iter = m_colorList.begin();
             iter != m_colorList.end(); ++iter)
        {
            painter.fillRect(iter->first, iter->second);
            bDrwa = true;
        }
    }

    //如果都没处理，窗口会是透明的,需要特出梳理一下
    if (!bDrwa)
    {
        QColor color;
        color.setRgb(0,100,120);
        painter.fillRect(rect(), color);
    }

}

void blurWindow::setwindowHearImage(const QString &strImagePath, bool bShowOnHoleWindow)
{
    m_imageHeaderImage.load(strImagePath);
    m_bHeaderImageShowHole = bShowOnHoleWindow;

    updateImageBuffer(size());

    update();
}

void blurWindow::setwindowHearImage(const QImage &strImage, bool bShowOnHoleWindow)
{
    m_imageHeaderImage = strImage;
    m_bHeaderImageShowHole = bShowOnHoleWindow;

    updateImageBuffer(size());

    update();
}

void blurWindow::setwindowFrontColor(const QList<QPair<QRect, QColor> > &listColor,
                                     const QColor &colorNormal)
{
    m_colorNormal = colorNormal;
    m_colorList = listColor;
    m_bSetFrontColor = true;

    updateImageBuffer(size());

    update();
}

void blurWindow::setOpacity(qreal opacity)
{
    m_realOpacity = opacity;

    updateImageBuffer(size());

    update();
}

qreal blurWindow::getOpacity()
{
    return m_realOpacity;
}

void blurWindow::paintEvent(QPaintEvent *event)
{
    QPainter p(this);
    p.drawImage(0,0,m_imageBuffer);

    windowFrame::paintEvent(event);
}

void blurWindow::resizeEvent(QResizeEvent *ev)
{
    updateImageBuffer(ev->size());

    windowFrame::resizeEvent(ev);
}
