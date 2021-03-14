#ifndef EMAILEX_H
#define EMAILEX_H

#include <QObject>
#include <QThread>
#include <QEventLoop>
#include <QMimeData>
#include "SmtpMime"

typedef struct
{
    bool bSsl;
    QString strHost;
    int iPort;
    QString strUser;
    QString strUserName;
    QString strPwd;
    QStringList toUsers;
    QStringList files;
    QString strSubject;
    QString strContent ;
}EMAIL_TO_ST;

typedef struct
{
    bool bOk;
    QString strErr;
}EMAIL_RESULT_ST;

//结构体初始化
/*
    to.strHost = "smtp.qq.com";
    to.iPort = 587;
    to.strUser = "123456@qq.com";
    to.strUserName = "panpan";
    to.strPwd  = "xxxxxx";
    to.toUsers<<"123456@qq.com";
    to.files<<"D:\\test\\1.txt";
    to.strSubject = "Send email test";
    to.strContent = "Hello world!";
*/

class EmailCore : public QObject
{
    Q_OBJECT
public:
    EmailCore(QObject *parent = 0);
    static bool send(const EMAIL_TO_ST &stTo, QString &strErr);
    static bool check(const EMAIL_TO_ST &stTo, QString &strErr);
};

//线程发送
class EmailThread : public QThread
{
    Q_OBJECT
public:
     EmailThread(const EMAIL_TO_ST &to, QObject *parent = 0);
    ~EmailThread();

    EMAIL_RESULT_ST getResult();
protected:
    virtual void run();

private:

signals:
    void emailRet(const EMAIL_RESULT_ST &st);

private:
    EMAIL_RESULT_ST m_stRet;
    EMAIL_TO_ST m_stTo;
};

#endif // EMAILEX_H
