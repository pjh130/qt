#ifndef TOOLBARCOMMON_H
#define TOOLBARCOMMON_H

#include <QWidget>

namespace Ui {
    class ToolbarCommon;
}

class ToolbarCommon : public QWidget
{
    Q_OBJECT

public:
    explicit ToolbarCommon(QWidget *parent = 0);
    ~ToolbarCommon();
public slots:
    void btnClicked00();
    void btnClicked01();
    void btnClicked02();
    void btnClicked03();
    void btnClicked04();
    void btnClicked05();
    void btnClicked06();
    void btnClicked07();
    void btnClicked08();
    void btnClicked09();
    void btnClicked10();
    void btnClicked11();
    void btnClicked12();
    void btnClicked13();
    void btnClicked14();
    void btnClicked15();
signals:
    void selColorChanged(QColor);
public:
    QColor getSelColor()
    {
        return selColor;
    }
    QString ColorToString(QColor c)
    {
        return QString("%1,%2,%3").arg (c.red ()).arg (c.green()).arg (c.blue ());
    }

private:
    Ui::ToolbarCommon *ui;
    QColor selColor;
};

#endif // TOOLBARCOMMON_H
