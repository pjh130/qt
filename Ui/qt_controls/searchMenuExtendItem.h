#ifndef SEARCHMENUEXTENDITEM_H
#define SEARCHMENUEXTENDITEM_H

#include <QWidget>
#include "comboitem.h"

namespace Ui {
    class searchMenuExtendItem;
}

class searchMenuExtendItem : public comboItem
{
    Q_OBJECT

public:
    explicit searchMenuExtendItem(QWidget *parent = 0);
    ~searchMenuExtendItem();

    void setInfo(const QPixmap &pixmap, const QString &strText);
    void setActiveStatue(bool bActive);

private:
    void paintEvent(QPaintEvent *);

private:
    Ui::searchMenuExtendItem *ui;
    bool m_bActived;
};

#endif // SEARCHMENUEXTENDITEM_H
