#ifndef COMBOBOX_H
#define COMBOBOX_H

#include <QWidget>
#include "comboboxlist.h"
#include <QLineEdit>
#include <QLabel>
#include <QList>
#include <QObject>
#include <QMutex>
#include <QIcon>

#define NOSELECTED -1

namespace Ui {
    class comboBox;
}

class comboBox : public QWidget
{
    Q_OBJECT

public:
    comboBox(QWidget *parent = 0);
    ~comboBox();

    void setDefaultString(const QString &);
    void setShowPixmap(bool bShow);
    void setEditable(bool bEditable);
    void clearEditText();
    void removeItem(int iIndex);
    void setCurrentIndex(int iIndex);
    int currentIndex();
    QString currentText();
    int count();
    QVariant itemData(int iIndex);
    QString itemText(int iIndex);
    QPixmap itemPixmap(int iIndex);
    void setEditText(const QString &strText);
    void setItemHeight(int iNormalHeight, int iActiveHeight);
    void setTextEditImageShow(const QPixmap &pixmap);
    void setItemText(int iIndex, const QString &strNewText);
    void setItemData(int iIndex, const QVariant &variant);

    void addItem(const QPixmap &pixmap, const QString &strMainText, const QString &strMinorText, const QVariant &data, bool bNeedDelButton = true);
    void addItem(const QPixmap &pixmap, const QString &strMainText, const QString &strMinorText, bool bNeedDelButton = true);
    void addItem(const QString &strMainText, const QString &strMinorText, bool bNeedDelButton = true);
    void insertItem(int iIndex, const QPixmap &pixmap, const QString &strMainText,
                 const QString &strMinorText, const QVariant &data, bool bNeedDelButton = true);

signals:
    void buttonClicked(int iIndex);
    void selectChanged(int iIndex);
    void textChanged();
    void sgn_removeItem(int);

private slots:
    void dealSelectChangedMsg(int iIndex);
    void slot_removeItem(int);
    void showListWindow();

private:
    void resizeEvent(QResizeEvent *);
    void reSortWindow();

private:
    Ui::comboBox *ui;
    comboboxList m_listWindow;

    QList<comboboxData> m_data;
    int m_iIndexSelected;

    bool m_bShowPixmap;
};

#endif // COMBOBOX_H
