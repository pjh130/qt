#ifndef RECTTOOLBAR_H
#define RECTTOOLBAR_H

#include <QWidget>
#include <QFrame>
#include "globalDataType.h"
namespace Ui {
    class RectToolBar;
}

class RectToolBar : public QFrame
{
    Q_OBJECT

public:
    explicit RectToolBar(QWidget *parent = 0);
    ~RectToolBar();
signals:
    void attrChanged();
public slots:
    void lineColorChanged(QColor color);
    void Clicked_1 ( bool checked = false );
    void Clicked_2 ( bool checked = false );
    void Clicked_3 ( bool checked = false );
public:
    qreal getLineWidth();
    QColor getLineColor();
private:
    Ui::RectToolBar *ui;
    qreal      lineWidth;
    QColor     colorUsed;
};

#endif // RECTTOOLBAR_H
