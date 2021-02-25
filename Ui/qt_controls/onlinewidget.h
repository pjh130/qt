#ifndef ONLINEWIDGET_H
#define ONLINEWIDGET_H

#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include <QMenu>
#include "public.h"

class onLineWidget : public QPushButton
{
    Q_OBJECT
public:
    explicit onLineWidget(QWidget *parent = 0);
    void setStatus(onLineStatus enStatus);
    onLineStatus getStatus();

signals:
    void statusChanged(int);

private slots:
    void statusButtonClicked();

private:
    QMenu m_menuStatus;

    QAction *m_actionOnLine;
    QAction *m_actionOffLine;
    QAction *m_actionLeaveLine;
    QAction *m_actionGooutLine;

    onLineStatus m_enStatus;
};

#endif // ONLINEWIDGET_H
