#include "systemTrayIcon.h"
#include <QEvent>
#include <QCursor>

systemTrayIcon::systemTrayIcon(QObject *parent) : QSystemTrayIcon(parent)
{
    connect(this, SIGNAL(activated(QSystemTrayIcon::ActivationReason)),
            this, SLOT(systemTrayIconActivated(QSystemTrayIcon::ActivationReason)));

    connect(&m_timer, SIGNAL(timeout()), this, SLOT(changeIcon()));

    m_bMouseHorer = false;
    m_timerCheckMousePos.start(300);
    connect(&m_timerCheckMousePos, SIGNAL(timeout()), this, SLOT(checkMousePos()));
}

systemTrayIcon::~systemTrayIcon()
{

}

void systemTrayIcon::setIcon(const QString &strNoLogInIconPath, const QString &strLogInIconPath)
{
    m_iconNoLogIn.addFile(strNoLogInIconPath);
    m_iconLogin.addFile(strLogInIconPath);

    QSystemTrayIcon::setIcon(m_iconNoLogIn);
}

void systemTrayIcon::coruscateIcon(const QString &strID, const QIcon &icon1, const QIcon &icon2)
{
    stopCoruscateIcon(true);

    m_strID = strID;

    m_i8ChangeTimes = 0;
    m_icon1 = icon1;
    m_icon2 = icon2;
    m_timer.start(500);
    changeIcon();
}

void systemTrayIcon::stopCoruscateIcon(bool bShowLoginedImage)
{
    if (m_timer.isActive())
    {
        m_timer.stop();
    }

    if (bShowLoginedImage)
    {
        QSystemTrayIcon::setIcon(m_iconLogin);
    }
    else
    {
        QSystemTrayIcon::setIcon(m_iconNoLogIn);
    }

    m_strID.clear();
}

void systemTrayIcon::systemTrayIconActivated(QSystemTrayIcon::ActivationReason enActivationReason)
{
    if (Context == enActivationReason)
    {
        emit showMainMenu();
    }
    else if (DoubleClick == enActivationReason)
    {
        if (!m_strID.isEmpty())
        {
            emit showUserMessage(m_strID);
        }
    }
    else if (Trigger == enActivationReason)
    {
        if (!m_strID.isEmpty())
        {
            emit showUserMessage(m_strID);
        }
        else
        {
            emit showMainWindow();
        }
    }
}

void systemTrayIcon::showLogining()
{
    coruscateIcon("", m_iconNoLogIn, m_iconLogin);
}

void systemTrayIcon::changeIcon()
{
    if (0 == m_i8ChangeTimes % 2)
    {
        QSystemTrayIcon::setIcon(m_icon1);
    }
    else
    {
        QSystemTrayIcon::setIcon(m_icon2);
    }

    m_i8ChangeTimes++;
}

void systemTrayIcon::checkMousePos()
{
    if (geometry().contains(QCursor::pos()))
    {
        if (!m_bMouseHorer)
        {
            m_bMouseHorer = true;
            emit mouseEnter();
        }
    }
    else
    {
        if (m_bMouseHorer)
        {
            m_bMouseHorer = false;
            emit mouseLeave();
        }
    }
}
