#ifndef AUTOHIDEWINDOW_H
#define AUTOHIDEWINDOW_H

#include "blurWindow.h"

class autoHideWindow : public blurWindow
{
    Q_OBJECT

public:
    autoHideWindow(QWidget *parent, Qt::WindowFlags f = 0);
    void startAutoClose(qreal iSecondDelay, bool bCloseTrends);

    // 返回值表示关闭倒计时定时器是否启动
    bool stopAutoClose();
    // 重启定时器
    void reStartAutoClose();

private slots:
    void countDownTimeOut();
    void closeTimerOut();

protected:
    void enterEvent(QEvent *);
    void leaveEvent(QEvent *);

private:
    // 退出时是否动态退出
    bool m_bCloseTrends;
    qint32 m_iSecondDelay;

    QTimer m_timerCountDown;
    QTimer m_timerClose;

    // 关闭窗体之前的透明度
    qreal m_realOpacityBefore;

    bool m_bHadStartAutoClose;
};

#endif // AUTOHIDEWINDOW_H
