#ifndef IMAGELISTWIDGET_H
#define IMAGELISTWIDGET_H

#include <QDialog>
#include <QSlider>
class skinItem;

class skinListwidget : public QDialog
{
    Q_OBJECT
public:
    explicit skinListwidget(QWidget *parent = 0);
    void exec(const QPoint &point);
    bool addImage(const QString &strImagePath, bool bShowDelButton = true);
    void deleteItem(qint8 i8Index);
    void setProgressBarValue(int iValue);
    void setSelectedBkgImg(int iIndex);
    qint8 getSelectedBkgIndex();
    qint8 getProgressBarValue();

private:
    void resizeEvent(QResizeEvent *);
    void init();
    qint8 calculateItemHeight();
    qint8 calculateItemWidth();
    void reSortImages();
    void resize(const QSize &);
    void resize(int, int);

private:
    QList<skinItem*> m_listpSkinItem;
    qint8 m_i8UsedCount;
    qint8 m_i8TopLine;
    qint8 m_i8ButtomLine;
    QSlider m_horizontalSlider;

signals:
    void sgn_mouseEnterItem(qint8, const QString &);
    void sgn_mouseLeaveItem(qint8);
    void sgn_deleteButtonClicked(qint8, const QString &);
    void sgn_addSkinButtonClicked();
    void sgn_itemSelectChanged(qint8, const QString &);
    void horizontalSliderValueChanged(int);
    void horizontalSliderReleased();

public slots:
    void mouseEnterItem(qint8, const QString &);
    void mouseLeaveItem(qint8);
    void deleteButtonClicked(qint8, const QString &);
    void itemSelected(qint8 i8Index, const QString &);
};

#endif // IMAGELISTWIDGET_H
