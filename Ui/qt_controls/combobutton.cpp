#include "combobutton.h"
#include <QKeyEvent>

#define SECELTICON ":/controls_res/Ok.png"

comboButton::comboButton(QWidget *parent) :
    QToolButton(parent)
{
    setFocusPolicy(Qt::StrongFocus);
    m_actionSetDefault = NULL;

    setMouseTracking(true);

    m_actionEnter = m_menuDefaultKey.addAction(QString::fromUtf8("press \"Enter\" key"));
    m_actionCtrlEnter = m_menuDefaultKey.addAction(QString::fromUtf8("press \"Ctrl + Enter\" key"));

    connect(&m_menuDefaultSentance, SIGNAL(triggered(QAction*)), this, SLOT(defaultSentenceSelected(QAction*)));
    connect(&m_menuDefaultKey, SIGNAL(triggered(QAction*)), this, SLOT(defaultKeySelected(QAction*)));

    setShutCut();
}


void comboButton::mouseReleaseEvent(QMouseEvent *e)
{
    if (isInDownRect(e->pos()))
    {
        QPoint point = pos();
        point.ry() += height();

        setDefaultSend(getKey2Send());
        m_menuDefaultKey.move(parentWidget()->mapToGlobal(point));
        m_menuDefaultKey.exec();
    }
    else
    {
        QToolButton::mouseReleaseEvent(e);
    }
}

void comboButton::mouseMoveEvent(QMouseEvent *e)
{
    QToolButton::mouseMoveEvent(e);

    if (isInDownRect(e->pos()))
    {
        setCursor(QCursor(Qt::PointingHandCursor));
    }
    else
    {
        setCursor(QCursor(Qt::CustomCursor));
    }
}

bool comboButton::isInDownRect(const QPoint &point)
{
    QPoint pointCurrent = point;
    if (width() - pointCurrent.x() < 20)
    {
        return true;
    }

    return false;
}

void comboButton::setDefaultSentance(const QStringList &listSentance, qint8 i8SelectedIndex)
{
    m_menuDefaultSentance.clear();

    for (qint8 i8Index = 0; i8Index < listSentance.size(); ++i8Index)
    {
        if (i8Index != i8SelectedIndex)
        {
            m_menuDefaultSentance.addAction(listSentance[i8Index]);
        }
        else
        {
            m_menuDefaultSentance.addAction(QIcon(SECELTICON), listSentance[i8Index]);
        }
    }

    m_actionSetDefault = m_menuDefaultSentance.addAction("set default sentence...");
}

void comboButton::defaultSentenceSelected(QAction* action)
{
    if (m_actionSetDefault != action)
    {
        emit SentenceSelected(action->text(), false);
    }
    else
    {
        emit SentenceSelected("", true);
    }
}

void comboButton::showDefaultSentence()
{
    QPoint point = pos();
    point.ry() += height();

    m_menuDefaultSentance.move(parentWidget()->mapToGlobal(point));
    m_menuDefaultSentance.exec();
}

void comboButton::setDefaultSend(qint32 iIndex)
{
    if (0 != iIndex)
    {
        m_actionCtrlEnter->setIcon(QIcon(SECELTICON));
        m_actionEnter->setIcon(QIcon());
    }
    else
    {
        m_actionCtrlEnter->setIcon(QIcon());
        m_actionEnter->setIcon(QIcon(SECELTICON));
    }
}

void comboButton::defaultKeySelected(QAction* action)
{
    if (m_actionEnter == action)
    {
        emit KeySendSelected(Enter2Send);
    }
    else if (m_actionCtrlEnter == action)
    {
        emit KeySendSelected(CtrlEnter2Send);
    }

    setShutCut();
}

Key2Send comboButton::getKey2Send()
{
    return Enter2Send;
}

void comboButton::keyPressEvent(QKeyEvent *event)
{
    QToolButton::keyPressEvent(event);

    switch(getKey2Send())
    {
    case Enter2Send:
        if (event->key() == Qt::Key_Enter || event->key() == Qt::Key_Return)
        {
            emit click();
        }
        break;

    case CtrlEnter2Send:
        if (Qt::ControlModifier == event->modifiers() && (event->key() == Qt::Key_Enter
               || event->key() == Qt::Key_Return))
        {
            emit click();
        }
        break;
    }
}

void comboButton::setShutCut()
{
    switch(getKey2Send())
    {
    case Enter2Send:
        setShortcut(QKeySequence(Qt::Key_Enter));
        break;

    default:
        setShortcut(QKeySequence(Qt::CTRL + Qt::Key_Enter));
        break;
    }
}
