#ifndef COMBOBOXITEM_H
#define COMBOBOXITEM_H

#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include "comboitem.h"

namespace Ui {
    class comboBoxItem;
}

class comboBoxItem : public comboItem
{
    Q_OBJECT

public:
    comboBoxItem(QWidget *parnet = 0);
    ~comboBoxItem();

    void setInfo(const QPixmap &pixmap, const QString &strMainText,
                 const QString &strMinorText, bool bHaveButton);

    void setShowButton(bool show);

signals:
    void buttonClicked(comboBoxItem *);

private slots:
    void on_pushButton_clicked();

private:
    void resizeEvent(QResizeEvent *);
    void reSortUi();

private:
    Ui::comboBoxItem *ui;
    bool m_bHaveButton;
    bool m_bShowButton;
};

#endif // COMBOBOXITEM_H
