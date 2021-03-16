#include "tcpsocketthread.h"

TcpSocketThread::TcpSocketThread(qintptr socketDescriptor, QObject *parent):
    QThread(parent)
{
    //注册自定义的信号槽参数
    qRegisterMetaType<SEND_DATA_ST>("SEND_DATA_ST");
    m_socketID = socketDescriptor;
    m_sockect = NULL;
    m_timer = NULL;
    m_bQuit = false;
}

TcpSocketThread::~TcpSocketThread()
{
    //这里不能停止timer
    closeSockect();
}

void TcpSocketThread::quitThread()
{
    if(m_timer)
    {
        m_timer->stop();
        m_timer->deleteLater();
        m_timer = NULL;
    }

    closeSockect();

    if(isRunning())
    {
        wait(1000);
        exit();
    }
}

void TcpSocketThread::closeSockect()
{
    if(m_sockect)
    {
        m_sockect->close();
        m_sockect->deleteLater();
        m_sockect = NULL;
    }
}

void TcpSocketThread::run()
{
    //connect加Qt::DirectConnection表示slot的执行线程就是信号发出者所在的线程
    if (m_socketID <= 0)
    {
        emit sockDisConnect(m_socketID, m_strIp, m_port, QThread::currentThread());
        return;
    }

    m_timer = new QTimer;
    connect(m_timer, SIGNAL(timeout()), this, SLOT(slotWork()), Qt::DirectConnection);
    m_timer->start(100);

    m_sockect = new QTcpSocket;
    m_sockect->setSocketDescriptor(m_socketID);
    m_strIp = m_sockect->peerAddress().toString();
    m_port = m_sockect->peerPort();
    connect(m_sockect,&QTcpSocket::readyRead,this,&TcpSocketThread::slotReadData, Qt::DirectConnection);
    dis = connect(m_sockect, &QTcpSocket::disconnected, this, &TcpSocketThread::slotDisconnect, Qt::DirectConnection);

    emit connectClient(m_socketID, m_strIp, m_port);
    qDebug() << "new connect-->"<<m_strIp<<":"<<m_port;

    exec();
}

void TcpSocketThread::slotWork()
{
    if(m_bQuit)
    {
        qDebug()<<"``````````stop timer````````";
        quitThread();
        return;
    }

    m_lock.lock();
    if (m_lstSenddata.isEmpty())
    {
        m_lock.unlock();
        return;
    }
    SEND_DATA_ST st = m_lstSenddata.takeFirst();
    m_lock.unlock();

//    qDebug()<<"TcpSocketThread::slotWork currentThreadId: "<<QThread::currentThreadId();
    qint64 send =  m_sockect->write(st.byData);
    if (send == st.byData.length())
    {
        //成功
        emit sendDataRet(m_socketID, st.strKey, true, "");
    } else {
        //失败
        emit sendDataRet(m_socketID, st.strKey, false, m_sockect->errorString());
    }
}

void TcpSocketThread::slotSendData(SEND_DATA_ST st)
{
    //    qDebug()<<"TcpSocketThread::slotSendData currentThreadId: "<<QThread::currentThreadId();
    if(m_sockect == NULL)
    {
        return;
    }

    if(st.socketID == m_socketID || -1 == st.socketID )
    {
        SEND_DATA_ST add;
        add.socketID = st.socketID;
        add.strKey = st.strKey;
        add.byData = st.byData;

        m_lock.lock();
        m_lstSenddata.append(add);
        m_lock.unlock();
    } else {
        //不做任何处理
    }
}

void TcpSocketThread::disConTcp(const qintptr socketID)
{
    if(m_sockect == NULL)
    {
        return;
    }

    if (socketID == m_socketID)
    {
        m_bQuit = true;
        //        m_sockect->disconnectFromHost();
    }
    else if (socketID == -1) //-1为全部断开
    {
        disconnect(dis); //先断开连接的信号槽，防止二次析构
        m_bQuit = true;
    }
}

void TcpSocketThread::slotDisconnect()
{
    //    qDebug()<<"TcpSocketThread::slotDisconnect";
    emit sockDisConnect(m_socketID, m_strIp, m_port, QThread::currentThread());//发送断开连接的用户信息
    m_bQuit = true;
}

void TcpSocketThread::slotReadData()
{
    if(m_sockect == NULL)
    {
        return;
    }

    //    qDebug()<<"TcpSocketThread::slotReadData currentThreadId: "<<QThread::currentThreadId();
    QByteArray data  = m_sockect->readAll();

    //收到的数据不做处理转发出去
    emit receiveData(m_socketID, data);
}

