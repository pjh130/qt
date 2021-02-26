#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_email_clicked()
{
    EMAIL_TO_ST to;
    EmailEx email;

    to.strHost = "smtp.qq.com";;
    to.iPort = 587;;
    to.strUser = "89284497@qq.com";
    to.strUserName = "panpan";
    to.strPwd  = "xxxx";
    to.toUsers<<"2209764788@qq.com";
    to.toUsers<<"pjh130@163.com";
    to.files<<"D:\\test\\1.txt";
    to.files<<"D:\\test\\2.txt";
    to.strSubject = "Send email test";
    to.strContent = "Hello world!";

    if(!email.send(to))
    {
        qDebug()<<email.getError();
    } else {
        qDebug()<<"Send email success!";
    }
}

void MainWindow::on_pushButton_excel_clicked()
{
    //在后台线程中使用QAxObject必须先初始化
    CoInitializeEx(NULL, COINIT_MULTITHREADED);

    QScopedPointer<ExcelBase> m_xls;
    QElapsedTimer timer;
    timer.start();
    if(m_xls.isNull())
        m_xls.reset(new ExcelBase);
    m_xls->create("D:\\test\\a.xlsx");
    m_xls->setProperty("Visible", false); // 不显示窗体
    m_xls->setProperty("DisplayAlerts", false);  // 不显示任何警告信息。
    qDebug()<<"create cost:"<<timer.elapsed()<<"ms";
    timer.restart();
    QList< QList<QVariant> > m_datas;
    for(int i=0;i<1000;++i)
    {
        QList<QVariant> rows;
        for(int j=0;j<100;++j)
        {
            rows.append(i*j);
        }
        m_datas.append(rows);
    }
    m_xls->setCurrentSheet(1);
    timer.restart();
    m_xls->writeCurrentSheet(m_datas);
    qDebug()<<"write cost:"<<timer.elapsed()<<"ms";

    //关闭表格
    if(!m_xls.isNull())
    {
        m_xls->save();
        m_xls->close();
    }
}

void MainWindow::on_pushButton_log_clicked()
{
    INI_LOG_ST init;
    LogEx::getClass().initLog(init);

    LogEx::getClass().writeLog("Hello world!");
    LogEx::getClass().writeLog("Test 1");
    LogEx::getClass().writeLog("Test 2", LEVEL_LOG);
    LogEx::getClass().writeLog("Test 3", LEVEL_EMAIL);
    LogEx::getClass().writeLog("Test 4", LEVEL_SMS);
}

void MainWindow::on_pushButton_network_clicked()
{
    NetworkAccessManagerEx *network = new NetworkAccessManagerEx();
    network->start();

    connect(this, SIGNAL(start()), network, SLOT(slotStart()));
    connect(this, SIGNAL(addWork(REQUEST_ST)), network, SLOT(slotAddWork(REQUEST_ST)));
    connect(network, SIGNAL(workResult(bool,QString,QByteArray)), this, SLOT(slotWorkResult(bool,QString,QByteArray)));

    emit start();

    REQUEST_ST st;
    st.method = REQUEST_METHOD_GET;
    st.strUrl = "http://www.baidu.com/";
    st.strTask = QUuid::createUuid().toString();

    emit addWork(st);
}

void MainWindow::on_pushButton_zip_clicked()
{
    int iTest = 0;
    if (iTest == 0)
    {
        bool bRet = JlCompress::compressFile("D:\\test\\new\\file.tar", "D:\\test\\1.txt");
        qDebug()<<"compressFile result: "<<bRet;
    } else if(iTest == 1) {
        QStringList files;
        files<<"D:\\test\\1.txt";
        files<<"D:\\test\\2.txt";
        files<<"D:\\test\\aaa\\3.txt";
        bool bRet = JlCompress::compressFiles("D:\\test\\new\\files.tar", files);
        qDebug()<<"compressFiles result: "<<bRet;
    } else if(iTest == 2) {
        bool bRet = JlCompress::compressDir("D:\\test\\new\\dir.tar", "D:\\test\\aaa");
        qDebug()<<"compressDir result: "<<bRet;
    } else if (iTest == 3) {
        QStringList ret = JlCompress::extractDir("D:\\test\\new\\file.tar", "D:\\test\\new\\up");
        qDebug()<<"extractDir result: "<<ret;
    } else if (iTest == 4) {
        QStringList ret = JlCompress::extractDir("D:\\test\\new\\files.tar", "D:\\test\\new\\up");
        qDebug()<<"extractDir result: "<<ret;
    } else if (iTest == 5) {
        QStringList ret = JlCompress::extractDir("D:\\test\\new\\dir.tar", "D:\\test\\new\\up");
        qDebug()<<"extractDir result: "<<ret;
    } else {

    }
}

void MainWindow::on_pushButton_thread_clicked()
{
    ThreadHandle::getClass().initThreadType(ThreadHandle::THREADSIZE, 1);
    QThread *pThread1 = ThreadHandle::getClass().getThread();
    ThreadHandle::getClass().getThread();
    ThreadHandle::getClass().getThread();
    ThreadHandle::getClass().getThread();
    ThreadHandle::getClass().getThread();
    QThread *pThread2 = ThreadHandle::getClass().getThread();
    qDebug()<<"currentThreadId1: "<<pThread1->currentThreadId();
    qDebug()<<"currentThreadId2: "<<pThread2->currentThreadId();

    QObject *obj = new QObject;
    qDebug()<<"currentThreadId obj1: "<<obj->thread()->currentThreadId();

    obj->moveToThread(pThread2);
    qDebug()<<"currentThreadId obj2: "<<obj->thread()->currentThreadId();
}

void MainWindow::slotWorkResult(bool bOk, QString strTask, QByteArray data)
{
    qDebug()<<"bOk: "<<bOk;
    qDebug()<<"strTask: "<<strTask;
    qDebug()<<"data: "<<data.length();

    QFile file("D:\\test\\network.html");
    if (!file.open(QIODevice::Append))
    {
        qDebug()<<"Failed to open file: " + file.errorString();
        return;
    }

    file.write(data);
    file.close();
}
