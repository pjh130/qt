#ifndef PUSHBUTTON_H
#define PUSHBUTTON_H

#include <QDialog>
#include <QList>
#include <QPair>
#include <QIcon>
#include <QString>

typedef qint8 Action;

class menu : public QDialog
{
public:
    explicit menu(QWidget *parent = 0);

    Action addAction(const QImage &image, const QString &text);
    Action addAction(const QString &text);
//    Action exec(const QPoint &point);
//    Action exec();
    int exec(const QPoint &point);
    int exec();

private:
    void paintEvent(QPaintEvent *);
    void reSizeMenu();
    void mousePressEvent(QMouseEvent *);
    Action isInItemRect(const QPoint &point);
    void mouseMoveEvent(QMouseEvent *);
    void leaveEvent(QEvent *);

private:
    Action m_menuTrigered;
    QList<QPair<QImage, QString> > m_listItem;

    Action m_mouseCurrentIn;
};

#endif // PUSHBUTTON_H
