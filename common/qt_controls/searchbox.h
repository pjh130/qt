#ifndef SEARCHBOX_H
#define SEARCHBOX_H

#include <QFrame>
#include <QPushButton>
#include <QLineEdit>
#include "searchBoxMenu.h"

namespace Ui {
    class searchBox;
}

class searchBox : public QFrame
{
    Q_OBJECT

public:
    searchBox(QWidget *parent = 0);
    ~searchBox();

    void setRecord(const QList<searchboxData> &);
    void clearRecord();
    void setCurrentIndex(qint8 i8Index);
    void setMaxShowRecord(int);
    bool getItemData(int iIndex, searchboxData &data);
    int getRecordCurrentSelected();
    void setExternItemData(const QList<searchExtendItemData> &listData);

signals:
    void textChanged(const QString&);
    void recordSelected(int);
    void extendItemSelected(int);

private:
    bool eventFilter(QObject *, QEvent *);
    void showListWindow();
    void resizeEvent(QResizeEvent *);
    void enterEvent(QEvent *);
    void leaveEvent(QEvent *);

private slots:
    void slot_recordSelected(int);
    void slot_extendItemClicked(int iIndex);

    void on_pushButton_clear_clicked();

private:
    Ui::searchBox *ui;
    QList<searchboxData> m_data;

    searchBoxMenu m_oListWindow;
    int m_iRecordSelected;
    int m_iExtendItemSelected;
};

#endif // SEARCHBOX_H
