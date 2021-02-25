#ifndef DOUBLELAYERLABLE_H
#define DOUBLELAYERLABLE_H

#include <QLabel>

class doubleLayerLable : public QLabel
{
public:
    explicit doubleLayerLable(QWidget *parent = 0);
    void setDistance(qint8 i8XDistance, qint8 iYDistance);
    void setColor(QColor colorfront, QColor colorBack);

private:
    void paintEvent(QPaintEvent *);

private:
    qint8 m_i8XDistance;
    qint8 m_i8YDistance;

    QColor m_colorfront;
    QColor m_colorBack;
};

#endif // DOUBLELAYERLABLE_H
