#ifndef WINDOWFRAME_H
#define WINDOWFRAME_H

#include "noframeDialog.h"
#include <QLabel>
#include <QTimer>

class windowFrame : public NoFrameDialog
{
    Q_OBJECT

public:
    windowFrame(QWidget *parent = 0, Qt::WindowFlags f = 0);
    ~windowFrame();

    void hideMaxButton(bool bHide);
    void hideMinButton(bool bHide);
    void hideCloseButton(bool bHide);

    void setBackgroudImage(const QString &strImage);
    QLabel* getCloseButton();
    QLabel* addTitlebutton(const QPixmap &pixmap, const QSize &size);

protected:
    void resizeEvent(QResizeEvent *);
    bool eventFilter(QObject *, QEvent *);
    void reSortTitleButton();

    virtual bool titleButtonClicked(QLabel *);

    void showBeforeSize();
    void showMaximized();

    void mouseDoubleClickEvent(QMouseEvent *event);

private slots:
    void checkTitleButtonClickTimeout();

private:
    bool m_isMaxSize;

    QSize m_sizeBefore;
    QPoint m_pointBefore;

    QTimer m_timerCheckTitlebuttonClick;
    bool m_bMousePressOnTitleButton;

    QList<QLabel*> m_lstCustomTitleButton;

    QLabel m_CloseButton;
    QLabel m_MinButton;
    QLabel m_MaxButton;
};

#endif // WINDOWFRAME_H
