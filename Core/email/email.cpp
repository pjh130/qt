#include "email.h"

EmailEx::EmailEx( QObject *parent) : QObject(parent)
{
}

QString EmailEx::getError()
{
    return m_strLastErr;
}

void EmailEx::setError(const QString &strErr)
{
    m_strLastErr = strErr;
}

void EmailEx::clearError()
{
    m_strLastErr.clear();
}

bool EmailEx::send(const EMAIL_TO_ST &stTo)
{
    clearError();

    bool bOk = true;

    SmtpClient smtp(stTo.strHost, stTo.iPort);

    //设置超时5分钟
    smtp.setSendMessageTimeout(1000*60*5);
    smtp.setResponseTimeout(1000*60*5);
    smtp.setConnectionTimeout(1000*60*5);

    smtp.setUser(stTo.strUser);
    smtp.setPassword(stTo.strPwd);

    MimeMessage message;
    //邮件标题
    message.setSubject(stTo.strSubject);

    EmailAddress sender(stTo.strUser, stTo.strUserName);
    message.setSender(&sender);


    //添加发送人
    QList<EmailAddress*> lstAddr;
    for(int i=0; i<stTo.toUsers.length(); i++)
    {
        //这里不new对象就不会发送成功多个收件人
        EmailAddress *to = new EmailAddress(stTo.toUsers.at(i), stTo.toUsers.at(i));
        message.addRecipient(to);
        lstAddr<<to;
    }

    //文字内容
    MimeText text;
    text.setText(stTo.strContent);
    message.addPart(&text);

    //发送的附件
    QList<MimeFile*> lstFile;
    for(int i=0; i<stTo.files.length();i++)
    {
        QString path = stTo.files.at(i);
        //判断文件是否存在
        if(QFile::exists(path))
        {
            //这里不new对象就会崩溃
            MimeFile *file = new MimeFile(new QFile(path));
            message.addPart(file);
            lstFile<<file;
        } else {
            setError("File not exist: " + path);
            bOk = false;

            break;
        }
    }

    if(bOk)
    {
        //连服务器
        if (!smtp.connectToHost()) {
            setError("Failed to connect to host!");
            bOk = false;
        } else {
            //登录
            if (!smtp.login()) {
                setError("Failed to login!");
                bOk = false;
            } else {
                //发送
                if (!smtp.sendMail(message)) {
                    setError("Failed to send mail!");
                    bOk = false;
                }
            }
            smtp.quit();
        }
    }

    //清理new出来的资源
    for(int i=0; i<lstAddr.length();i++)
    {
        lstAddr.at(i)->deleteLater();
    }

    //清理new出来的资源
    for(int i=0; i<lstFile.length();i++)
    {
        lstFile.at(i)->deleteLater();
    }

    return bOk;
}
