#include "autoHideWindow.h"

autoHideWindow::autoHideWindow(QWidget *parent, Qt::WindowFlags f)
    : blurWindow(parent, f)
{
    m_bCloseTrends = true;
    m_iSecondDelay = 0xFFFFFFFF;
    m_bHadStartAutoClose = false;

    connect(&m_timerCountDown, SIGNAL(timeout()), this, SLOT(countDownTimeOut()));
    connect(&m_timerClose, SIGNAL(timeout()), this, SLOT(closeTimerOut()));
}

void autoHideWindow::startAutoClose(qreal iSecondDelay, bool bCloseTrends)
{
    m_iSecondDelay = iSecondDelay;
    m_bCloseTrends = bCloseTrends;
    m_realOpacityBefore = getOpacity();
    m_bHadStartAutoClose = true;

    m_timerCountDown.start(m_iSecondDelay * 1000);
}

void autoHideWindow::reStartAutoClose()
{
    if (stopAutoClose())
    {
        setOpacity(m_realOpacityBefore);
    }

    startAutoClose(m_iSecondDelay, m_bCloseTrends);
}

void autoHideWindow::countDownTimeOut()
{
    if (m_bCloseTrends)
    {
        m_timerClose.start(100);
    }
    else
    {
        reject();
    }
    m_timerCountDown.stop();
}

void autoHideWindow::closeTimerOut()
{
    if (getOpacity() <= 0.1)
    {
        m_timerClose.stop();
        reject();
    }
    else
    {
        setOpacity(getOpacity() - 0.03);
    }
}

void autoHideWindow::enterEvent(QEvent *ev)
{
    blurWindow::enterEvent(ev);

    if (stopAutoClose())
    {
        setOpacity(m_realOpacityBefore);
    }
}

void autoHideWindow::leaveEvent(QEvent *ev)
{
    blurWindow::leaveEvent(ev);

    if (m_bHadStartAutoClose)
    {
        startAutoClose(m_iSecondDelay, m_bCloseTrends);
    }
}

bool autoHideWindow::stopAutoClose()
{
    bool bTimerActived = false;
    if (m_timerClose.isActive())
    {
        bTimerActived = true;
        m_timerClose.stop();
    }
    if (m_timerCountDown.isActive())
    {
        bTimerActived = true;
        m_timerCountDown.stop();
    }

    return bTimerActived;
}
