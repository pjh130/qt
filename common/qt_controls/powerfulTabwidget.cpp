#include "powerfultabwidget.h"
#include <QTabBar>

powerfulTabWidget::powerfulTabWidget(QWidget *parent) :
    QTabWidget(parent)
{
}

void powerfulTabWidget::setNoCloseButton(int iIndex, const QSize &sizeItem)
{
    QTabBar* pTabBar = tabBar();
    if (NULL != pTabBar)
    {
        QWidget *pWidget = new QWidget;
        pWidget->resize(sizeItem);
        pTabBar->setTabButton(iIndex, QTabBar::RightSide, pWidget);
    }
}

void powerfulTabWidget::feed2Full()
{
    QTabBar* pTabBar = tabBar();
    if (NULL != pTabBar)
    {
        for (int iIndex = 0; iIndex < count(); ++iIndex)
        {
            QWidget *pWidget = new QWidget;
            pWidget->setMaximumSize(pTabBar->width() / count() / 2, pTabBar->height());
            pWidget->setMinimumSize(pTabBar->width() / count() / 2, pTabBar->height());
            pTabBar->setTabButton(iIndex, QTabBar::LeftSide, pWidget);
        }
    }
}
