#ifndef QTWIN_H
#define QTWIN_H

#include <QColor>
#include <QWidget>

class WindowNotifier;

class QtWin
{
public:
    static void blurWidget(QWidget *widget);

private:
    static bool enableAeroWindow(QWidget *widget, bool enable = true);
    static bool extendFrameIntoClientArea(QWidget *widget,
                                          int left = -1, int top = -1,
                                          int right = -1, int bottom = -1);
    static bool isCompositionEnabled();
    static QColor colorizatinColor();

    static WindowNotifier *windowNotifier();

    friend class WindowNotifier;
};

#endif // QTWIN_H
