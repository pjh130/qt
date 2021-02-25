#ifndef CALCULATEMSGCOUNT_H
#define CALCULATEMSGCOUNT_H

#include <QObject>
#include <QMap>
#include <QString>
#include <QMetaType>
#include <QMutex>

typedef struct
{
    QString strHeadrPath;
    QString strID;
    qint32 iCount;
    QString strDetail;
}messageInfo;

// 目前只支持单线程访问

class calculateMsgCount : public QObject
{
    Q_OBJECT
public:
    explicit calculateMsgCount(QObject *parent = 0);
    bool getLastestUserInfo(messageInfo &);
    void setNoReadCount(quint32 iCount);
    void clear();
    QList<messageInfo> getMessages();

signals:
    void messageCountChanged(qint32 iCount);
    void lastMessageUserChanged(const QString &strHeadrPath, const QString &strID, const QString &strDetail);
    void lastMsgShowButNoReadChanged(const QString &strHeadrPath, const QString &strID, const QString &strDetail);
    void msgCleared();

public slots:
    void messageNotice(const QString &strHeaderpath, const QString &strWho,
                       bool bCome, const QString &strDetail);
    void msgNoticeShowButNoRead(const QString &strHeaderpath, const QString &strWho,
                       bool bCome, const QString &strDetail);

private:
    QList<messageInfo> m_msgCountBuf;
    QList<messageInfo> m_msgShowButNoRead;
    quint32 m_iMsgCome;

    quint32 m_iNoReadMsgCount;

    QMutex m_mutex;
};

#endif // CALCULATEMSGCOUNT_H
