#ifndef SEARCHMENUITEM_H
#define SEARCHMENUITEM_H

#include <QWidget>
#include "comboitem.h"

namespace Ui {
    class searchMenuItem;
}

class searchMenuItem : public comboItem
{
    Q_OBJECT

public:
    explicit searchMenuItem(QWidget *parent = 0);
    ~searchMenuItem();

    void setInfo(const QPixmap &pixmap, const QString &strText);

private:
    bool eventFilter(QObject *, QEvent *);

private:
    Ui::searchMenuItem *ui;
};

#endif // SEARCHMENUITEM_H
