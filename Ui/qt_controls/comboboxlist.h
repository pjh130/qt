#ifndef COMBOBOXLIST_H
#define COMBOBOXLIST_H

#include <QVariant>
#include "comboboxitem.h"
#include "comboitemlist.h"

typedef struct
{
    QPixmap pixmap;
    QString strMainText;
    QString strMinorText;
    QVariant data;
    bool bNeedDelButton;
}comboboxData;

class comboboxList : public comboItemList
{
    Q_OBJECT

public:
    comboboxList(QWidget *parent = 0, Qt::WindowFlags f = 0);
    ~comboboxList();

    void setData(const QList<comboboxData> &data);

signals:
    void buttonClicked(int iIndex);

private:
    void setItemActived(comboItem*, bool bActive);

private slots:
    void slot_buttonClicked(comboBoxItem *);
};

#endif // COMBOBOXLIST_H
