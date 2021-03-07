#ifndef TEXTTOOLBAR_H
#define TEXTTOOLBAR_H

#include <QWidget>
#include <QFrame>
#include "globalDataType.h"

namespace Ui {
    class TextToolBar;
}

class TextToolBar : public QFrame
{
    Q_OBJECT

public:
    explicit TextToolBar(QWidget *parent = 0);
    ~TextToolBar();
public:
    int getFontSize(){return fontSize;};
    QColor getFontColor(){return colorUsed;}
signals:
    void attrChanged();
public slots:
    void fontSizeChanged ( int index );
    void fontColorChanged(QColor color);
//    void Clicked_1 ( bool checked = false );
//    void Clicked_2 ( bool checked = false );
//    void Clicked_3 ( bool checked = false );
private:
    Ui::TextToolBar *ui;
    int      fontSize;
    QColor   colorUsed;
};

#endif // TEXTTOOLBAR_H
