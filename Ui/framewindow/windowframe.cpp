#include "windowframe.h"
#include <QApplication>
#include <QDesktopWidget>

#define iControlDistance 3

windowFrame::windowFrame(QWidget *parent, Qt::WindowFlags f) : NoFrameDialog(parent, f)
{
    m_isMaxSize = false;
    m_bMousePressOnTitleButton = false;

    connect(&m_timerCheckTitlebuttonClick, SIGNAL(timeout()), this, SLOT(checkTitleButtonClickTimeout()));
    m_timerCheckTitlebuttonClick.start(100);

    m_CloseButton.setPixmap(QPixmap(":/res/close.png"));
    m_MinButton.setPixmap(QPixmap(":/res/minimum.png"));
    m_MaxButton.setPixmap(QPixmap(":/res/maximum.png"));

    m_CloseButton.setParent(this);
    m_MinButton.setParent(this);
    m_MaxButton.setParent(this);

    m_CloseButton.show();
    m_MinButton.show();
    m_MaxButton.show();

    m_CloseButton.installEventFilter(this);
    m_MinButton.installEventFilter(this);
    m_MaxButton.installEventFilter(this);

    m_CloseButton.resize(39, 20);
    m_MinButton.resize(28, 20);
    m_MaxButton.resize(28, 20);

    hideMaxButton(false);
    hideMinButton(false);
    hideCloseButton(false);
    setObjectName("myframe");
    setStyleSheet("windowFrame#myframe{border-image:url(:/res/BG004.jpg)}");
//    setStyleSheet("background-image:url(:/res/BG004.jpg);");
}

windowFrame::~windowFrame()
{
    for (QList<QLabel*>::iterator iter = m_lstCustomTitleButton.begin(); iter != m_lstCustomTitleButton.end(); ++iter)
    {
        delete *iter;
    }
    m_lstCustomTitleButton.clear();
}

bool windowFrame::titleButtonClicked(QLabel *)
{
    return false;
}

bool windowFrame::eventFilter(QObject *object, QEvent *event)
{
    if (QEvent::MouseButtonRelease == event->type())
    {
        if (Qt::LeftButton == ((QMouseEvent *)event)->button())
        {
            if (&m_CloseButton == object)
            {
                if (!titleButtonClicked(&m_CloseButton))
                {
                    close();
                }
                m_bMousePressOnTitleButton = false;
                return true;
            }
            else if (&m_MaxButton == object)
            {
                m_bMousePressOnTitleButton = false;
                if (!m_isMaxSize)
                {
                    showMaximized();
                }
                else
                {
                    showBeforeSize();
                }
                return true;
            }
            else if (&m_MinButton == object)
            {
                m_bMousePressOnTitleButton = false;
                hide();
                return true;
            }
            else
            {
                for (QList<QLabel*>::iterator iter = m_lstCustomTitleButton.begin(); iter != m_lstCustomTitleButton.end(); ++iter)
                {
                    if (*iter == object)
                    {
                        m_bMousePressOnTitleButton = false;
                        return titleButtonClicked(*iter);
                    }
                }
            }
        }
    }
    else if (QEvent::MouseButtonPress == event->type())
    {
        if (Qt::LeftButton == ((QMouseEvent *)event)->button())
        {
            if (&m_CloseButton == object)
            {
                m_bMousePressOnTitleButton = true;
                return true;
            }
            else if (&m_MaxButton == object)
            {
                m_bMousePressOnTitleButton = true;
                return true;
            }
            else if (&m_MinButton == object)
            {
                m_bMousePressOnTitleButton = true;
                return true;
            }
            else
            {
                for (QList<QLabel*>::iterator iter = m_lstCustomTitleButton.begin(); iter != m_lstCustomTitleButton.end(); ++iter)
                {
                    if (*iter == object)
                    {
                        m_bMousePressOnTitleButton = true;
                        return true;
                    }
                }
            }
        }
    }

    return NoFrameDialog::eventFilter(object, event);
}

void windowFrame::resizeEvent(QResizeEvent *event)
{
    NoFrameDialog::resizeEvent(event);

    reSortTitleButton();

    m_CloseButton.raise();
    m_MinButton.raise();
    m_MaxButton.raise();
}

void windowFrame::reSortTitleButton()
{
    QSize sizeMainWindow = size();

    int iXPos = sizeMainWindow.width();

    if (!m_CloseButton.isHidden())
    {
        QSize sizeCloseButton = m_CloseButton.size();
        QPoint pointCloseButton(0, -1);
        pointCloseButton.rx() = sizeMainWindow.width() - sizeCloseButton.width() + 1;
        m_CloseButton.move(pointCloseButton);

        iXPos = pointCloseButton.x();
    }

    if (!m_MaxButton.isHidden())
    {
        QSize sizeMaxButton = m_MaxButton.size();
        QPoint pointMaxButton(0, -1);
        pointMaxButton.rx() = iXPos - sizeMaxButton.width();
        m_MaxButton.move(pointMaxButton);

        iXPos = pointMaxButton.x();
    }

    if (!m_MinButton.isHidden())
    {
        QSize sizeMinButton = m_MinButton.size();
        QPoint pointMinButton(0, -1);
        pointMinButton.rx() = iXPos - sizeMinButton.width();
        m_MinButton.move(pointMinButton);

        iXPos = pointMinButton.x();
    }

    iXPos += iControlDistance;
    QPoint pointMinButton = m_MinButton.pos();
    for (QList<QLabel*>::iterator iter = m_lstCustomTitleButton.begin(); iter != m_lstCustomTitleButton.end(); ++iter)
    {
        if (!(*iter)->isHidden())
        {
            QSize sizeButton = (*iter)->size();
            QPoint pointButton(0, -1);
            pointButton.rx() = iXPos - sizeButton.width() - iControlDistance;
            pointButton.ry() = pointMinButton.ry();
            (*iter)->move(pointButton);

            iXPos = pointButton.x();
        }
    }
}

void windowFrame::showBeforeSize()
{
    m_isMaxSize = false;
    resize(m_sizeBefore);
    move(m_pointBefore);
    QPixmap pixmap(":/res/maximum.png");
    m_MaxButton.setPixmap(pixmap);

    setMoveAble(true);
}

void windowFrame::showMaximized()
{
    m_sizeBefore = size();
    m_pointBefore = pos();
    m_isMaxSize = true;

    setMoveAble(false);

    QRect rectDestop = QApplication::desktop()->availableGeometry();
    move(0,0);
    resize(rectDestop.width(), rectDestop.height());

    QPixmap pixmap(":/res/resume.png");
    m_MaxButton.setPixmap(pixmap);
}

void windowFrame::hideMaxButton(bool bHide)
{
    m_MaxButton.setVisible(!bHide);

    reSortTitleButton();
}

void windowFrame::hideMinButton(bool bHide)
{
    m_MinButton.setVisible(!bHide);

    reSortTitleButton();
}

void windowFrame::hideCloseButton(bool bHide)
{
    m_CloseButton.setVisible(!bHide);

    reSortTitleButton();
}

void windowFrame::mouseDoubleClickEvent(QMouseEvent *event)
{
    if (Qt::LeftButton == event->button() && !m_MaxButton.isHidden())
    {
        if (m_isMaxSize)
        {
            showBeforeSize();
        }
        else
        {
            showMaximized();
        }
    }

    NoFrameDialog::mouseDoubleClickEvent(event);
}

QLabel* windowFrame::getCloseButton()
{
    return &m_CloseButton;
}

QLabel *windowFrame::addTitlebutton(const QPixmap &pixmap, const QSize &size)
{
    QLabel *pLabel = new QLabel(this);
    if (NULL == pLabel)
    {
        return NULL;
    }

    m_lstCustomTitleButton.push_back(pLabel);
    pLabel->setPixmap(pixmap);
    pLabel->installEventFilter(this);
    pLabel->show();
    pLabel->resize(size);
    pLabel->setCursor(QCursor(Qt::PointingHandCursor));
    pLabel->setAlignment(Qt::AlignTop);

    reSortTitleButton();

    return pLabel;
}

void windowFrame::checkTitleButtonClickTimeout()
{
    QPoint pointCursor = QCursor::pos();
    pointCursor = this->mapFromGlobal(pointCursor);

    if (!m_CloseButton.isHidden() && m_CloseButton.frameGeometry().contains(pointCursor))
    {
        if (m_bMousePressOnTitleButton)
        {
            m_CloseButton.setAlignment(Qt::AlignBottom);
        }
        else
        {
            m_CloseButton.setAlignment(Qt::AlignVCenter);
        }
    }
    else
    {
        m_CloseButton.setAlignment(Qt::AlignTop);
    }

    if (!m_MinButton.isHidden() && m_MinButton.frameGeometry().contains(pointCursor))
    {
        if (m_bMousePressOnTitleButton)
        {
            m_MinButton.setAlignment(Qt::AlignBottom);
        }
        else
        {
            m_MinButton.setAlignment(Qt::AlignVCenter);
        }
    }
    else
    {
        m_MinButton.setAlignment(Qt::AlignTop);
    }

    if (!m_MaxButton.isHidden() && m_MaxButton.frameGeometry().contains(pointCursor))
    {
        if (m_bMousePressOnTitleButton)
        {
            m_MaxButton.setAlignment(Qt::AlignBottom);
        }
        else
        {
            m_MaxButton.setAlignment(Qt::AlignVCenter);
        }
    }
    else
    {
        m_MaxButton.setAlignment(Qt::AlignTop);
    }

    for (QList<QLabel*>::iterator iter = m_lstCustomTitleButton.begin(); iter != m_lstCustomTitleButton.end(); ++iter)
    {
        if (!(*iter)->isHidden() && (*iter)->frameGeometry().contains(pointCursor))
        {
            if (m_bMousePressOnTitleButton)
            {
                (*iter)->setAlignment(Qt::AlignBottom);
            }
            else
            {
                (*iter)->setAlignment(Qt::AlignVCenter);
            }
        }
        else
        {
            (*iter)->setAlignment(Qt::AlignTop);
        }
    }
}
