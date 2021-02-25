#ifndef SYSTEMTRAYICON_H
#define SYSTEMTRAYICON_H

#include <QSystemTrayIcon>
#include <QTimer>
#include <QIcon>

class systemTrayIcon : public QSystemTrayIcon
{
    Q_OBJECT

public:
    systemTrayIcon(QObject *parent = 0);
    ~systemTrayIcon();

    void setIcon(const QString &strNoLogInIconPath, const QString &strLogInIconPath);
    void coruscateIcon(const QString &strID, const QIcon &icon1, const QIcon &icon2);
    void stopCoruscateIcon(bool bShowLoginedImage);
    void showLogining();

private slots:
    void systemTrayIconActivated(QSystemTrayIcon::ActivationReason);
    void changeIcon();
    void checkMousePos();

signals:
    void showUserMessage(const QString& strWho);
    void showMainWindow();
    void showMainMenu();
    void mouseEnter();
    void mouseLeave();

private:
    QIcon m_iconNoLogIn;
    QIcon m_iconLogin;

    QTimer m_timer;
    QIcon m_icon1;
    QIcon m_icon2;
    qint8 m_i8ChangeTimes;

    QString m_strID;

    QTimer m_timerCheckMousePos;
    bool m_bMouseHorer;
};

#endif
