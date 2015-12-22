#include "onlinewidget.h"

onLineWidget::onLineWidget(QWidget *parent) :
    QPushButton(parent)
{
    setStatus(onLine_On);
    setAutoDefault(false);

    connect(this, SIGNAL(clicked()), this, SLOT(statusButtonClicked()));
}

void onLineWidget::setStatus(onLineStatus enStatus)
{
    if (enStatus == m_enStatus)
    {
        return;
    }

    switch(enStatus)
    {
    case onLine_On:
        setIcon(QPixmap(":/controls_res/onLine.png"));
        break;

    case onLine_meeting:
        setIcon(QPixmap(":/controls_res/meeting.png"));
        break;

    case onLine_Leave:
        setIcon(QPixmap(":/controls_res/leave.png"));
        break;

    case onLine_Out:
        setIcon(QPixmap(":/controls_res/goout.png"));
        break;
    }

    m_enStatus = enStatus;
    emit statusChanged(enStatus);
}

void onLineWidget::statusButtonClicked()
{
    m_menuStatus.clear();
    m_actionOnLine = m_menuStatus.addAction(QPixmap(":/controls_res/onLine_menu.png"), tr("on line"));
    m_actionLeaveLine = m_menuStatus.addAction(QPixmap(":/controls_res/leave_menu.png"), tr("leave"));
    m_actionGooutLine = m_menuStatus.addAction(QPixmap(":/controls_res/goout_menu.png"), tr("go out"));
    m_actionOffLine = m_menuStatus.addAction(QPixmap(":/controls_res/meeting_menu.png"), tr("meeting"));

    QAction *action = m_menuStatus.exec(mapToGlobal(QPoint(0,  height())));

    if (NULL == action)
    {
        return;
    }

    if (action == m_actionOnLine)
    {
        setStatus(onLine_On);
    }
    else if (action == m_actionOffLine)
    {
        setStatus(onLine_meeting);
    }
    else if(action == m_actionLeaveLine)
    {
        setStatus(onLine_Leave);
    }
    else if(action == m_actionGooutLine)
    {
        setStatus(onLine_Out);
    }
}

onLineStatus onLineWidget::getStatus()
{
    return m_enStatus;
}
