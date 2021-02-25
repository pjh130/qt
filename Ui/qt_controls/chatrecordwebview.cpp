#include "chatrecordwebview.h"
#include <QWebFrame>
#include <QDragEnterEvent>
#include <QDir>
#include <QProcess>
#include <QDesktopServices>
#include <QDebug>
#include "public.h"

chatRecordWebView::chatRecordWebView(QWidget *parent) :
    QWebView(parent)
{
    m_bFinishedInit = false;
    setUrl(QUrl("qrc:/app/chatMessages.html"));
    initWebView(*this);

    connect(page()->mainFrame(), SIGNAL(javaScriptWindowObjectCleared()),
                     this, SLOT(addJSObject()));
    connect(this, SIGNAL(loadFinished(bool)), this, SLOT(pageLoadFinish(bool)));

    page()->setLinkDelegationPolicy(QWebPage::DelegateAllLinks);
}

void chatRecordWebView::addJSObject()
{
    page()->mainFrame()->addToJavaScriptWindowObject(QString("chatRecordWebView"), this);
}

void chatRecordWebView::pageLoadFinish(bool bOk)
{
    if (bOk)
    {
        m_bFinishedInit = true;

        for (QList<QMap<QString, QVariant> >::iterator iter = m_listMsgRecord.begin(); iter != m_listMsgRecord.end(); ++iter)
        {
            emit sgn_messageCome(*iter);
            emit textChanged();
        }

        m_listMsgRecord.clear();
    }
}
#include <QFile>
void chatRecordWebView::addSendMsg(qint64 i64UserID, qint64 i64InId, const QString &strName,
     const QString &strTime, const QString &strText, const QString &strHeaderImage)
{
    QMap<QString, QVariant> object;

    object["messageType"] = "send";
    object["name"] = strName;
    object["time"] = strTime;
    object["text"] = strText;
    object["userId"] = QString::number(i64UserID);
    object["headPic"] = strHeaderImage;
    object["inId"] = QString::number(i64InId);


    QDir dir;
    dir.mkpath("./temp/");
        QFile file("./temp/send.txt");
        file.open(QIODevice::Append);
        file.write(strText.toUtf8());
        file.write("\r\n");
        file.close();

    if (m_bFinishedInit)
    {
        emit sgn_messageCome(object);
        emit textChanged();
    }
    else
    {
        m_listMsgRecord.push_back(object);
    }
}

void chatRecordWebView::addRecvMsg(qint64 i64UserID, qint64 i64InId, const QString &strName,
     const QString &strTime, const QString &strText, const QString &strHeaderImage)
{
    QMap<QString, QVariant> object;

    object["messageType"] = "recv";
    object["name"] = strName;
    object["time"] = strTime;
    object["text"] = strText;
    object["userId"] = QString::number(i64UserID);
    object["headPic"] = strHeaderImage;
    object["inId"] = QString::number(i64InId);

    QDir dir;
    dir.mkpath("./temp/");
    QFile file("./temp/recv.txt");
    file.open(QIODevice::Append);
    file.write(strText.toUtf8());
    file.write("\r\n");
    file.close();

    if (m_bFinishedInit)
    {
        emit sgn_messageCome(object);
        emit textChanged();
    }
    else
    {
        m_listMsgRecord.push_back(object);
    }
}

void chatRecordWebView::addNotifyMsg(const QString &strText)
{
    QMap<QString, QVariant> object;

    object["messageType"] = "notify";
    object["text"] = "<font color=gray>" + strText + "</font>";

    QDir dir;
    dir.mkpath("./temp/");
    QFile file("./temp/Notify.txt");
    file.open(QIODevice::Append);
    file.write(strText.toUtf8());
    file.write("\r\n");
    file.close();

    if (m_bFinishedInit)
    {
        emit sgn_messageCome(object);
        emit textChanged();
    }
    else
    {
        m_listMsgRecord.push_back(object);
    }
}

void chatRecordWebView::clearText()
{
    QMap<QString, QVariant> object;

    object["messageType"] = "clear";

    if (m_bFinishedInit)
    {
        emit sgn_messageCome(object);
        emit textChanged();
    }
    else
    {
        m_listMsgRecord.push_back(object);
    }
}

void chatRecordWebView::movePosition(QTextCursor::MoveOperation opt)
{
    // only to down
    if (opt == QTextCursor::End)
    {
        QMap<QString, QVariant> object;

        object["messageType"] = "scroll2Buttom";

        if (m_bFinishedInit)
        {
            emit sgn_messageCome(object);
        }
        else
        {
            m_listMsgRecord.push_back(object);
        }
    }
}

bool chatRecordWebView::event(QEvent *pEvent)
{
    if (QEvent::ContextMenu == pEvent->type())
    {
        //return true;
    }
    return QWebView::event(pEvent);
}

void chatRecordWebView::keyReleaseEvent(QKeyEvent *ev)
{
    if (ev->key() == Qt::Key_C && (ev->modifiers() == Qt::ControlModifier))
    {
        triggerPageAction(QWebPage::Copy);
    }

    QWebView::keyReleaseEvent(ev);
}

void chatRecordWebView::openfile(const QStringList & urls)
{
    if (!urls.isEmpty())
    {
        QString strFilePath = urls[0];
        if (strFilePath.indexOf("file:///") != 0)
        {
            QDesktopServices::openUrl("file:///" + strFilePath);
        }
        else
        {
            QDesktopServices::openUrl(strFilePath);
        }
    }
}

void chatRecordWebView::openPath(const QStringList & urls)
{
    if (!urls.isEmpty())
    {
#ifdef Q_OS_WIN
        if (urls.size() >= 2)
        {
            QString strFilePath = urls[1];
            strFilePath = QDir::toNativeSeparators(strFilePath);
            QString str_openCommand = QString("explorer /select, %1").arg(strFilePath);
            qDebug()<<"Open FilePath:"<<str_openCommand;
            QProcess::startDetached(str_openCommand);
        }
#else
        QDesktopServices::openUrl("file:///" + urls[0]);
#endif
    }
}

void chatRecordWebView::slot_openChatPanel(const QStringList & urls)
{
    if (!urls.isEmpty())
    {
        QString strUserId = urls[0];
        emit sgn_openChatWindow(strUserId.toLongLong());
    }
}

void chatRecordWebView::notifyImageCome(const QString &strImageId, const QString &strImageUrl)
{
    QMap<QString, QVariant> object;

    object["messageType"] = "imageLoad";
    object["id"] = strImageId;
    object["url"] = strImageUrl;

    if (m_bFinishedInit)
    {
        emit sgn_messageCome(object);
        emit textChanged();
    }
    else
    {
        m_listMsgRecord.push_back(object);
    }

    QDir dir;
    dir.mkpath("./temp/");
    QFile file("./temp/ImageCome.txt");
    file.open(QIODevice::Append);
    file.write(strImageId.toUtf8());
    file.write("\r\n");
    file.write(strImageUrl.toUtf8());
    file.write("\r\n\r\n");
    file.close();
}

void chatRecordWebView::addRecvFileRecord(const QString &strFilePath, const QString &strFromWho)
{
    QMap<QString, QVariant> object;

    QString strFileName = strFilePath;
    strFileName = strFileName.replace('/', '\\');
    strFileName = strFileName.right(strFileName.length() - (strFileName.lastIndexOf('\\') + 1));
    object["messageType"] = "recvFile";
    object["fileName"] = strFilePath;
    object["showInfo"] = tr("receive a file from ") + strFromWho + ":";
    object["fileBaseName"] = strFileName;
    object["openButtonName"] = tr("open file");
    object["openPathName"] = tr("open path");
    object["pathName"] = strFilePath.left(strFilePath.length() - strFileName.length());

    QDir dir;
    dir.mkpath("./temp/");
    QFile file("./temp/RecvFileRecord.txt");
    file.open(QIODevice::Append);
    file.write(strFilePath.toUtf8());
    file.write("\r\n");
    file.close();

    if (m_bFinishedInit)
    {
        emit sgn_messageCome(object);
    }
    else
    {
        m_listMsgRecord.push_back(object);
    }
}

void chatRecordWebView::enableOpenChat(bool bEnable)
{
    QMap<QString, QVariant> object;

    object["messageType"] = "enableOpenChat";
    if (bEnable)
    {
        object["enable"] = "1";
    }
    else
    {
        object["enable"] = "0";
    }

    if (m_bFinishedInit)
    {
        emit sgn_messageCome(object);
    }
    else
    {
        m_listMsgRecord.push_back(object);
    }
}

