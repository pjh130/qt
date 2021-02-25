#ifndef NUMBERBUTTON_H
#define NUMBERBUTTON_H

#include <QWidget>

namespace Ui
{
    class numberButton;
}

class numberButton : public QWidget
{
    Q_OBJECT

public:
    explicit numberButton(QWidget *parent = 0);
    ~numberButton();

    void setNumber(qint32 iNumber);
    void setIcon(const QPixmap &pximap);

private:
    void mouseReleaseEvent(QMouseEvent *);

signals:
    void clicked();

private:
    Ui::numberButton *ui;
    qint32 m_iNumber;
};

#endif // NUMBERBUTTON_H
