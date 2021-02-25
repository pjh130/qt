#ifndef COMBOITEM_H
#define COMBOITEM_H

#include <QWidget>

class comboItem : public QWidget
{
    Q_OBJECT
public:
    explicit comboItem(QWidget *parent = 0);
    void setBackgroundColor(const QColor &);
    void enableMouseEnterEvent(bool bEnable);

signals:
    void currentSelect(comboItem*);
    void mouseEnter(comboItem *);

protected:
    void mouseReleaseEvent(QMouseEvent *);
    void enterEvent(QEvent *);
    void paintEvent(QPaintEvent *);

private:
    QColor m_colorBackground;
    bool m_EnableMouseEnterEvent;
};

#endif // COMBOITEM_H
