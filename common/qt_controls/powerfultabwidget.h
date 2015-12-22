#ifndef TABWIDGET_H
#define TABWIDGET_H

#include <QTabWidget>

class powerfulTabWidget : public QTabWidget
{
public:
    explicit powerfulTabWidget(QWidget *parent = 0);

    void setNoCloseButton(int iIndex, const QSize &sizeItem);
    void feed2Full();
};

#endif // TABWIDGET_H
