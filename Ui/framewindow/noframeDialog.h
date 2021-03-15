#ifndef NOFRAMEWINDOW_H
#define NOFRAMEWINDOW_H

#include <QDialog>
#include <QEvent>
#include <QMouseEvent>
#include <QtDebug>

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
//    bool event(QEvent *event);
    void mousePressEvent(QMouseEvent *);
    void mouseMoveEvent(QMouseEvent *);
    void mouseReleaseEvent(QMouseEvent *event);
    void resizeEvent(QResizeEvent *);
    void keyPressEvent(QKeyEvent *);
    void focusOutEvent(QFocusEvent *);
    void leaveEvent(QEvent *);

    int GetMouseRegion(int x, int y);    //判断鼠标的位置
    int GetMouseRegionNew(int x, int y); //判断鼠标的位置
    void SetMouseCursor(int x, int y);   //设置图标
private:
    QPoint last_point_;             //记录放大之前的位置
    QPoint last_position_;          //窗口上一次的位置

    bool m_bMousePress;
    bool m_bMoveAble;

    //鼠标位于界面的位置
    enum MousePosition
    {
        kMousePositionLeftTop = 11,
        kMousePositionTop = 12,
        kMousePositionRightTop = 13,
        kMousePositionLeft = 21,
        kMousePositionMid = 22,
        kMousePositionRight = 23,
        kMousePositionLeftButtom = 31,
        kMousePositionButtom = 32,
        kMousePositionRightButtom = 33,
    };

    //定义一个边界
    const int kMouseRegionLeft = 10;
    const int kMouseRegionTop = 10;
    const int kMouseRegionButtom = 10;
    const int kMouseRegionRight = 10;

    int mouse_press_region_ = kMousePositionMid; //鼠标点击的区域
};

#endif // NOFRAMEWINDOW_H
