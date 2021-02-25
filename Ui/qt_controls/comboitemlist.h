#ifndef ITEMLIST_H
#define ITEMLIST_H

#include <QDialog>
#include <QPushButton>
#include <QTimer>
#include <QScrollBar>

class comboItem;

class comboItemList : public QDialog
{
    Q_OBJECT
public:
    explicit comboItemList(QWidget *parent = 0, Qt::WindowFlags f = 0);
    ~comboItemList();

    void setItemHeight(int iNormalHeight, int iActiveHeight);
    void deleteItem(int iIndex);
    void setMaxShowItem(int iMaxShowItem);
    void setWidth(int iWidth);
    void setItemNormalColor(const QColor &);
    void setItemActiveColor(const QColor &);
    void setItem(const QList<comboItem*> &itemList);

private:
    void reScollwindow();
    void reHeightItem();
    void reSetScrollBarRange();
    void clearAllExtendItem();
    void setScrollBarValue(int iValue);

protected:
    void addItem(const QList<comboItem*> &itemList);
    void addExtendItem(const QList<comboItem*> &itemList);
    void clearAllItem();
    void setExtendItem(const QList<comboItem*> &itemList);
    void keyPressEvent(QKeyEvent *);
    virtual void setItemActived(comboItem*, bool bActive);
    virtual void setExtendItemActived(comboItem*, bool bActive);
    void resizeEvent(QResizeEvent *);

signals:
    void selectChanged(int iIndex);
    void extendItemClicked(int iIndex);
    void sizeChanged(const QSize &size, const QSize &oldSize);

private slots:
    void itemClicked(comboItem*);
    void itemMouseEnter(comboItem *);
    void scrollValueChange(int);

protected:
    int m_iActiveIndex;
    int m_iMaxShowItem;
    int m_iFirstShowIndex;
    int m_iNormalHeight;
    int m_iActiveHeight;
    int m_iExtendItemHeight;
    QScrollBar m_scrollBar;
    QList<comboItem*> m_lstWidgetItem;
    QList<comboItem*> m_lstExtendItem;

    QColor m_colorItemNormal;
    QColor m_colorItemActive;
};

#endif // ITEMLIST_H
