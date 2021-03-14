#include "emailex.h"

EmailCore::EmailCore( QObject *parent) : QObject(parent)
{
}

bool EmailCore::send(const EMAIL_TO_ST &stTo, QString &strErr)
{
    //检验基本参数
    if(!check(stTo, strErr))
    {
        return false;
    }

    bool bOk = true;
    SmtpClient smtp(stTo.strHost, stTo.iPort, stTo.bSsl ? SmtpClient::SslConnection : SmtpClient::TcpConnection);

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

    //如果是临时对象消失，程序会崩溃
    MimeText text;
    MimeHtml html;
    //做一个简单的判断区分html和普通文本
    if(stTo.strContent.startsWith("<") && stTo.strContent.endsWith(">")
            && stTo.strContent.contains("<html>") && stTo.strContent.contains("</html>"))
    {
        //构建邮件正文
        html.setHtml(stTo.strContent);
        message.addPart(&text);
    } else {
        //文字内容
        text.setText(stTo.strContent);
        message.addPart(&text);
    }

    //发送的附件
    QList<MimeFile*> lstFile;
    for(int i=0; i<stTo.files.length(); i++)
    {
        QString strfile = stTo.files.at(i);
        //这里不new对象就会崩溃, 由于check()函数已经检验了文件存在
        MimeFile *file = new MimeFile(new QFile(strfile));
        message.addPart(file);
        lstFile<<file;
    }

    if(bOk)
    {
        //连服务器
        if (!smtp.connectToHost()) {
            strErr = "Failed to connect to host!";
            bOk = false;
        } else {
            //登录
            if (!smtp.login()) {
                strErr = "Failed to login!";
                bOk = false;
            } else {
                //发送
                if (!smtp.sendMail(message)) {
                    strErr = "Failed to send mail!";
                    bOk = false;
                }
            }
            smtp.quit();
        }
    }
//return false;
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

bool EmailCore::check(const EMAIL_TO_ST &stTo, QString &strErr)
{
    if (stTo.strHost.isEmpty())
    {
        strErr = "Host is empty!";
        return false;
    }

    if (stTo.iPort <= 0 )
    {
        strErr = "Port error: " + QString::number(stTo.iPort);
        return false;
    }

    if (stTo.strUser.isEmpty())
    {
        strErr = "User is empty!";
        return false;
    }

    if (stTo.strPwd.isEmpty())
    {
        strErr = "Password is empty!";
        return false;
    }

    if (stTo.strSubject.isEmpty())
    {
        strErr = "Subject is empty!";
        return false;
    }

    if (stTo.toUsers.isEmpty())
    {
        strErr = "To users is empty!";
        return false;
    }

    //判断附件是否合法
    for(int i=0; i<stTo.files.length();i++)
    {
        QString path = stTo.files.at(i);
        //判断文件是否存在
        if(!QFile::exists(path))
        {
            strErr = "File not exist: " + path;
            return false;
        }
    }

    return true;
}

EmailThread::EmailThread(const EMAIL_TO_ST &to, QObject *parent): QThread(parent)
{
    //注册自定义的信号槽参数
    qRegisterMetaType<QPrivateSignal>("QPrivateSignal");

    m_stTo.strHost = to.strHost;
    m_stTo.iPort = to.iPort;
    m_stTo.strUser = to.strUser;
    m_stTo.strUserName = to.strUserName;
    m_stTo.strPwd = to.strPwd;
    m_stTo.toUsers = to.toUsers;
    m_stTo.files = to.files;
    m_stTo.strSubject = to.strSubject;
    m_stTo.strContent = to.strContent;
}

EmailThread::~EmailThread()
{
}

EMAIL_RESULT_ST EmailThread::getResult()
{
    return m_stRet;
}

void EmailThread::run()
{
    m_stRet.bOk = EmailCore::send(m_stTo, m_stRet.strErr);

    emit emailRet(m_stRet);
    qDebug()<<"EmailThread::run currentThreadId: "<<currentThreadId();
}

