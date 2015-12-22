#ifndef BLURWINDOW_H
#define BLURWINDOW_H

#include "windowframe.h"

class blurWindow : public windowFrame
{
public:
    blurWindow(QWidget *parent = 0, Qt::WindowFlags f = 0);
    ~blurWindow();

    void setBackgroudImage(const QString &strImagePath);
    void setBackgroudImage(const QImage &image);
    void setwindowHearImage(const QString &strImagePath, bool bShowOnHoleWindow);
    void setwindowHearImage(const QImage &strImage, bool bShowOnHoleWindow);
    void setwindowFrontColor(const QList<QPair<QRect, QColor> > &listColor,
                             const QColor &colorNormal);
    void setOpacity(qreal opacity);
    qreal getOpacity();

private:
    void updateImageBuffer(const QSize &size);

protected:
    void resizeEvent(QResizeEvent *);
    void paintEvent(QPaintEvent *);

private:
    QImage m_imageBackgroud;
    QImage m_imageHeaderImage;
    qreal m_realOpacity;
    bool m_bHeaderImageShowHole;

    // 用于缓冲，支持低端显卡
    QImage m_imageBuffer;
    QList<QPair<QRect, QColor> > m_colorList;
    QColor m_colorNormal;
    bool m_bSetFrontColor;
};

#endif
