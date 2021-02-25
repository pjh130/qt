#include "dynamicwidget.h"

dynamicWidget::dynamicWidget(QWidget *parent) :
    QWidget(parent)
{
    m_i8CurrentShowIndex = -1;
    connect(&m_timer, SIGNAL(timeout()), this, SLOT(dynamicShowWidget()));
}

void dynamicWidget::addWidget(QWidget *pWidget)
{
    if (NULL == pWidget)
    {
        return;
    }

    pWidget->resize(size());
    pWidget->setParent(this);
    pWidget->hide();
    pWidget->show();

    if (m_lstWidget.isEmpty())
    {
        pWidget->move(0, 0);
        m_i8CurrentShowIndex = 0;
    }
    else
    {
        pWidget->move(0, m_lstWidget[m_lstWidget.size() - 1]->pos().y() + size().height());
    }

    m_lstWidget.push_back(pWidget);
}

void dynamicWidget::showIndex(qint8 i8Index)
{
    if (i8Index < 0 || i8Index >= m_lstWidget.size())
    {
        return;
    }

    m_lstShowIndex.push_back(i8Index);

    if (!m_timer.isActive())
    {
        dynamicShowWidget();
        m_timer.start(20);
    }
}

void dynamicWidget::resizeEvent(QResizeEvent *event)
{
    QWidget::resizeEvent(event);

    qint8 i8Index = 0;
    for (QList<QWidget*>::iterator iter = m_lstWidget.begin(); iter != m_lstWidget.end(); ++iter, ++i8Index)
    {
        (*iter)->resize(size());

        if (i8Index < m_i8CurrentShowIndex)
        {
            (*iter)->move(0, (m_i8CurrentShowIndex - i8Index) * size().height() * -1);
        }
        else if (i8Index > m_i8CurrentShowIndex)
        {
            (*iter)->move(0, (i8Index - m_i8CurrentShowIndex) * size().height());
        }
    }
}

void dynamicWidget::moveOtherWidget(bool bShowWidow)
{
    if (m_i8CurrentShowIndex < 0 || m_i8CurrentShowIndex >= m_lstWidget.size())
    {
        return;
    }

    QPoint posCurrentShow = m_lstWidget[m_i8CurrentShowIndex]->pos();

    qint8 i8Index = 0;
    for (QList<QWidget*>::iterator iter = m_lstWidget.begin(); iter != m_lstWidget.end(); ++iter, ++i8Index)
    {
        if (i8Index < m_i8CurrentShowIndex)
        {
            (*iter)->move(0, (m_i8CurrentShowIndex - i8Index) * size().height() * -1 + posCurrentShow.y());
            (*iter)->setVisible(bShowWidow);
        }
        else if (i8Index > m_i8CurrentShowIndex)
        {
            (*iter)->move(0, (i8Index - m_i8CurrentShowIndex) * size().height() + posCurrentShow.y());
            (*iter)->setVisible(bShowWidow);
        }
    }
}

void dynamicWidget::dynamicShowWidget()
{
    if (m_lstShowIndex.isEmpty())
    {
        return;
    }
    if (m_lstShowIndex[0] < 0 || m_lstShowIndex[0] >= m_lstWidget.size())
    {
        m_lstShowIndex.removeAt(0);

        if (m_lstShowIndex.isEmpty())
        {
            m_timer.stop();
            return;
        }
    }

    m_i8CurrentShowIndex = m_lstShowIndex[0];

    bool bMoveOk = false;
    QPoint posCurrentWidget = m_lstWidget[m_i8CurrentShowIndex]->pos();
    m_lstWidget[m_i8CurrentShowIndex]->show();
    if (posCurrentWidget.y() < size().height() / 8 && posCurrentWidget.y() > size().height() / 8 * -1)
    {
        m_lstWidget[m_i8CurrentShowIndex]->move(0, 0);
        m_lstShowIndex.removeAt(0);

        if (m_lstShowIndex.isEmpty())
        {
            m_timer.stop();
        }

        bMoveOk = true;

        emit showWindowOk(m_i8CurrentShowIndex);
    }
    else if (posCurrentWidget.y() > 0)
    {
        posCurrentWidget.ry() -= size().height() / 8;
        m_lstWidget[m_i8CurrentShowIndex]->move(posCurrentWidget);
    }
    else if (posCurrentWidget.y() < 0)
    {
        posCurrentWidget.ry() += size().height() / 8;
        m_lstWidget[m_i8CurrentShowIndex]->move(posCurrentWidget);
    }

    moveOtherWidget(!bMoveOk);
}

void dynamicWidget::removeWidget(QWidget *pWidget)
{
    qint8 i8Index = 0;
    for (QList<QWidget*>::iterator iter = m_lstWidget.begin(); iter != m_lstWidget.end(); ++iter, ++i8Index)
    {
        if (*iter == pWidget)
        {
            m_lstWidget.erase(iter);

            if (m_lstWidget.isEmpty())
            {
                m_i8CurrentShowIndex = -1;
            }
            else if (m_i8CurrentShowIndex > 0)
            {
                showIndex(m_i8CurrentShowIndex - 1);
            }

            return;
        }
    }
}

void dynamicWidget::showWidget(QWidget *pWidget)
{
    qint8 i8Index = 0;
    for (QList<QWidget*>::iterator iter = m_lstWidget.begin(); iter != m_lstWidget.end(); ++iter, ++i8Index)
    {
        if (*iter == pWidget)
        {
            showIndex(i8Index);
            return;
        }
    }
}

qint8 dynamicWidget::getCurrentIndex()
{
    return m_i8CurrentShowIndex;
}
