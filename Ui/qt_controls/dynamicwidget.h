#ifndef DYNAMICWIDGET_H
#define DYNAMICWIDGET_H

#include <QWidget>
#include <QTimer>

class dynamicWidget : public QWidget
{
    Q_OBJECT

public:
    explicit dynamicWidget(QWidget *parent = 0);

    void addWidget(QWidget *pWidget);
    void showIndex(qint8 i8Index);
    void removeWidget(QWidget *pWidget);
    void showWidget(QWidget *pWidget);
    qint8 getCurrentIndex();

private slots:
    void dynamicShowWidget();

signals:
    void showWindowOk(qint8 iIndex);

private:
    void resizeEvent(QResizeEvent *);
    void moveOtherWidget(bool bShowWidow);

private:
    QList<QWidget*> m_lstWidget;
    qint8 m_i8CurrentShowIndex;

    QList<qint8> m_lstShowIndex;

    QTimer m_timer;
};

#endif // DYNAMICWIDGET_H
