#include "calculatemsgcount.h"
#include "windowmanager.h"

calculateMsgCount::calculateMsgCount(QObject *parent) :
    QObject(parent)
{
    m_iMsgCome = 0;
    m_iNoReadMsgCount = 0;
}

bool calculateMsgCount::getLastestUserInfo(messageInfo &info)
{
    QMutexLocker locker(&m_mutex);

    if (m_msgCountBuf.isEmpty())
    {
        return false;
    }
    else
    {
        info = m_msgCountBuf[m_msgCountBuf.size() - 1];
        return true;
    }
}

void calculateMsgCount::setNoReadCount(quint32 iCount)
{
    m_iNoReadMsgCount = iCount;
    emit messageCountChanged(m_iNoReadMsgCount + m_iMsgCome);
}

void calculateMsgCount::clear()
{
    m_mutex.lock();
    m_msgCountBuf.clear();
    m_msgShowButNoRead.clear();

    m_iMsgCome = 0;
    m_iNoReadMsgCount = 0;

    m_mutex.unlock();

    emit msgCleared();
}

void calculateMsgCount::messageNotice(const QString &strHeaderpath, const QString &strWho,
                                      bool bCome, const QString &strDetail)
{
    m_mutex.lock();

    bool bNew = true;
    for (QList<messageInfo>::iterator iter = m_msgCountBuf.begin();
         iter != m_msgCountBuf.end(); ++iter)
    {
        if (iter->strID == strWho)
        {
            bNew = false;
            if (bCome)
            {
                ++m_iMsgCome;
                iter->iCount++;
                iter->strDetail = strDetail;
            }
            else
            {
                m_iMsgCome -= iter->iCount;
                iter = m_msgCountBuf.erase(iter);
            }

            break;
        }
    }

    if (bNew && bCome)
    {
        messageInfo msgInfo;
        msgInfo.strHeadrPath = strHeaderpath;
        msgInfo.strID = strWho;
        msgInfo.iCount = 1;
        msgInfo.strDetail = strDetail;
        m_msgCountBuf.push_back(msgInfo);
        ++m_iMsgCome;
    }

    m_mutex.unlock();

    emit messageCountChanged(m_iNoReadMsgCount + m_iMsgCome);

    if (!bCome)
    {
        bool bEmpty = false;
        {
            QMutexLocker locker(&m_mutex);

            bEmpty = m_msgCountBuf.isEmpty();
        }
        if (bEmpty)
        {
            emit lastMessageUserChanged("", "", "");

            {
                QMutexLocker locker(&m_mutex);

                bEmpty = m_msgShowButNoRead.isEmpty();
            }

            if (!m_msgShowButNoRead.isEmpty())
            {
                m_mutex.lock();
                messageInfo info = m_msgShowButNoRead[m_msgShowButNoRead.size() - 1];
                m_mutex.unlock();

                emit lastMsgShowButNoReadChanged(info.strHeadrPath, info.strID, info.strDetail);
            }
        }
        else
        {
            emit lastMessageUserChanged(m_msgCountBuf[m_msgCountBuf.length() - 1].strHeadrPath,
                 m_msgCountBuf[m_msgCountBuf.length() - 1].strID,
                 m_msgCountBuf[m_msgCountBuf.length() - 1].strDetail);
        }
    }
    else
    {
        emit lastMessageUserChanged(strHeaderpath, strWho, strDetail);
    }
}

void calculateMsgCount::msgNoticeShowButNoRead(
    const QString &strHeaderpath, const QString &strWho, bool bCome, const QString &strDetail)
{
    m_mutex.lock();

    bool bNew = true;
    for (QList<messageInfo>::iterator iter = m_msgShowButNoRead.begin();
         iter != m_msgShowButNoRead.end(); ++iter)
    {
        if (iter->strID == strWho)
        {
            bNew = false;
            if (bCome)
            {
                iter->iCount++;
                iter->strDetail = strDetail;
            }
            else
            {
                iter = m_msgShowButNoRead.erase(iter);
            }

            break;
        }
    }

    if (bNew && bCome)
    {
        messageInfo msgInfo;
        msgInfo.strHeadrPath = strHeaderpath;
        msgInfo.strID = strWho;
        msgInfo.iCount = 1;
        msgInfo.strDetail = strDetail;
        m_msgShowButNoRead.push_back(msgInfo);
    }

    bool bEmpty = m_msgCountBuf.isEmpty();
    m_mutex.unlock();

    if (bEmpty)
    {
        if (!bCome)
        {
            m_mutex.lock();
            bEmpty = m_msgShowButNoRead.isEmpty();
            m_mutex.unlock();

            if (bEmpty)
            {
                emit lastMsgShowButNoReadChanged("", "", "");
            }
            else
            {
                m_mutex.lock();
                messageInfo info = m_msgShowButNoRead[m_msgShowButNoRead.size() - 1];
                m_mutex.unlock();

                emit lastMsgShowButNoReadChanged(info.strHeadrPath, info.strID, info.strDetail);
            }
        }
        else
        {
            emit lastMsgShowButNoReadChanged(strHeaderpath, strWho, strDetail);
        }
    }
}

QList<messageInfo> calculateMsgCount::getMessages()
{
    QMutexLocker locker(&m_mutex);

    return m_msgCountBuf;
}
