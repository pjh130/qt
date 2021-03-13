#ifndef NOFRAMEWINDOW_H
#define NOFRAMEWINDOW_H

#include <QDialog>
#include <QEvent>
#include <QMouseEvent>

class NoFrameDialog : public QDialog
{
    Q_OBJECT

public:
    NoFrameDialog(QWidget *parent = 0, Qt::WindowFlags f = 0);
    void setMoveAble(bool bMoveAble);
    void setVisible(bool bVisible);

signals:
    void LButtonDoubleClicked();
    void windowHidden();
    void sizeChanged(const QSize &);

protected:
    void mousePressEvent(QMouseEvent *);
    void mouseMoveEvent(QMouseEvent *);
    void mouseReleaseEvent(QMouseEvent *event);
    void resizeEvent(QResizeEvent *);
    void keyPressEvent(QKeyEvent *);
    void focusOutEvent(QFocusEvent *);
    void leaveEvent(QEvent *);

private:
    QPoint m_WindowPos;
    QPoint m_MousePos;
    QPoint m_dPos;

    bool m_bMousePress;
    bool m_bMoveAble;
};

#endif // NOFRAMEWINDOW_H
