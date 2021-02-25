#ifndef EMAIL_H
#define EMAIL_H

#include <QObject>
#include "SmtpMime"

typedef struct
{
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

//结构体初始化
/*
    to.strHost = "smtp.qq.com";;
    to.iPort = 587;;
    to.strUser = "123456@qq.com";
    to.strUserName = "panpan";
    to.strPwd  = "xxxxxx";
    to.toUsers<<"123456@qq.com";
    to.files<<"D:\\test\\1.txt";
    to.strSubject = "Send email test";
    to.strContent = "Hello world!";
*/


class EmailEx : public QObject
{
    Q_OBJECT
public:
    explicit EmailEx(QObject *parent = 0);

    QString getError();
    bool send(EMAIL_TO_ST stTo);

private:
    void setError(QString strErr);
    void clearError();

signals:

public slots:

private:
    QString m_strLastErr;

};

#endif // EMAIL_H
