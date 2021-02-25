#ifndef CHATRECORDWEBKIT_H
#define CHATRECORDWEBKIT_H

#include <QWebView>
#include <QMap>
#include <QVariant>
#include <QTextCursor>

class chatRecordWebView : public QWebView
{
    Q_OBJECT
public:
    explicit chatRecordWebView(QWidget *parent = 0);

    void addSendMsg(qint64 i64UserID, qint64 i64InId, const QString &strName,
       const QString &strTime, const QString &strText, const QString &strHeaderImage);
    void addRecvMsg(qint64 i64UserID, qint64 i64InId, const QString &strName,
       const QString &strTime, const QString &strText, const QString &strHeaderImage);
    void addNotifyMsg(const QString &strText);
    void clearText();
    void movePosition(QTextCursor::MoveOperation);
    void notifyImageCome(const QString &strImageId, const QString &strImageUrl);
    void addRecvFileRecord(const QString &strFilePath, const QString &strFromWho);
    void enableOpenChat(bool);

private:
    bool event(QEvent *);
    void keyReleaseEvent(QKeyEvent *);

signals:
    void sgn_messageCome(const QMap<QString, QVariant> &object);
    void textChanged();
    void sgn_openChatWindow(qint64);

private slots:
    void addJSObject();
    void pageLoadFinish(bool);

public slots:
    void openfile(const QStringList & urls);
    void openPath(const QStringList & urls);
    void slot_openChatPanel(const QStringList & urls);

private:
    bool m_bFinishedInit;
    QList<QMap<QString, QVariant> > m_listMsgRecord;
};

#endif // CHATRECORDWEBKIT_H
