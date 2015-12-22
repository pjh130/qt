#ifndef SKINITEM_H
#define SKINITEM_H

#include <QWidget>
#include <QPixmap>
#include <QPoint>

class skinItem : public QWidget
{
    Q_OBJECT
public:
    explicit skinItem(QWidget *parent = 0);
    void setImage(const QString &strImagePath);
    void setImage(const QString &strNormalImagePath, const QString &strMouseOnImagePath);
    void setShowDelButton(bool bShow);
    bool getShowDelButton();
    void setIndex(qint8 iIndex);
    bool isSelected();
    void setSelected(bool bSelected);
    QString getImagePath();

private:
    void paintEvent(QPaintEvent *);
    void enterEvent(QEvent *);
    void leaveEvent(QEvent *);
    void resizeEvent(QResizeEvent *);
    bool event(QEvent *);
    void rePlaceDelButton();

signals:
    void mouseEnter(qint8, const QString &);
    void mouseLeave(qint8);
    void deleteButtonClicked(qint8, const QString &);
    void selected(qint8, const QString &);

private:
    bool m_bSelected;
    QImage m_imageNormal;
    QImage m_imageMouseOn;
    bool m_bMouseOn;
    bool m_bShowDelButton;
    QImage m_imageDelete;
    qint8 m_i8Index;
    QString m_strImagePath;

    QPoint m_pointDeleteButton;
};

#endif // SKINITEM_H
