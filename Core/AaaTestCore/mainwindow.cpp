#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    qDebug()<<"MainWindow: "<<QThread::currentThreadId();
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
    init.strLogDir = "D:\\test\\log";
    LogEx::getClass().initClass(init);

    LogEx::getClass().writeLog("Hello world!");
    LogEx::getClass().writeLog("Test 1");
    LogEx::getClass().writeLog("Test 2", LEVEL_LOG);
    LogEx::getClass().writeLog("Test 3", LEVEL_EMAIL);
    LogEx::getClass().writeLog("Test 4", LEVEL_SMS);

    QMessageLogContext context;
    LogEx::getClass().customLog(QtDebugMsg, context, "Test 5");
    LogEx::getClass().customLog(QtWarningMsg, context, "Test 6");
    LogEx::getClass().customLog(QtCriticalMsg, context, "Test 7");
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

    TcpServer *ser = new TcpServer;
    ser->listen(QHostAddress::Any,6666);
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
    qDebug()<<"on_pushButton_thread_clicked: "<<QThread::currentThreadId();
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

void MainWindow::on_pushButton_sql_clicked()
{
    int i= 0;
    switch(i) {
    case 0:
        testSqlite();
        break;
    case 1:
        testMysql();
        break;
    case 2:
        testOdbc();
        break;
    case 3:
        testPsql();
        break;
    case 4:
        break;
    case 5:
        break;
    case 6:
        break;
    case 7:
        break;
    case 8:
        break;
    default:
        break;
    }



}

void MainWindow::testSqlite()
{
    INI_DB_ST st;
    st.strDatabaseName = "my.db";

    if(SqliteEx::getClass().initDb(st))
    {
        qDebug()<<"Success to init db sqllite!";
    } else {
        qDebug()<<"Failed to init db: "<<SqliteEx::getClass().getDatabase().lastError().text();
        return;
    }

    qDebug()<<"tables:    "<<SqliteEx::getClass().tables();

    bool bOk;
    //判断表是否存在
    QString str = "SELECT COUNT(*) as CNT FROM sqlite_master WHERE type = 'table' AND name = 'students'";

    bool bFindTable = false;
    bOk = SqliteEx::getClass().getQuery().exec(str);
    if (bOk)
    {
        qDebug()<<"exec ok: ";
        while(SqliteEx::getClass().getQuery().next())
        {
            int i = SqliteEx::getClass().getQuery().value("CNT").toInt();
            int j = SqliteEx::getClass().getQuery().value(0).toInt();
            qDebug()<<"CNT: "<<i<<"  RecNo:"<<j;
            if (i>=1)
            {
                bFindTable = true;
                break;
            }
        }
    } else {
        qDebug()<<"exec fail: "<<SqliteEx::getClass().getDatabase().lastError().text();
    }

    //没有找到表就创建
    if (!bFindTable)
    {
        //创建一个students表,标题分别为id、name、score、class
        bOk = SqliteEx::getClass().getQuery().exec("CREATE TABLE students ("
                                                   "id INTEGER PRIMARY KEY AUTOINCREMENT, "
                                                   "name VARCHAR(40) NOT NULL, "
                                                   "score INTEGER NOT NULL, "
                                                   "class VARCHAR(40) NOT NULL)");
        if (bOk)
        {
            qDebug()<<"exec ok";
        } else {
            qDebug()<<"exec fail: "<<SqliteEx::getClass().getDatabase().lastError().text();
            return;
        }

        //插入数据
        for (int i = 0; i< 10; ++i)
        {
            SqliteEx::getClass().getQuery().prepare("INSERT INTO students (id, name, score, class) VALUES (:id, :name, :score, :class)");
            SqliteEx::getClass().getQuery().bindValue(":name", QString("smith_%1").arg(i+1));
            SqliteEx::getClass().getQuery().bindValue(":score", 80+i);
            SqliteEx::getClass().getQuery().bindValue(":class", QString::number(i+1));
            SqliteEx::getClass().getQuery().exec();
        }
    } else {
        qDebug()<<"students table is exist!";
    }

    //查询数据
    str = "SELECT * FROM students";
    bOk = SqliteEx::getClass().getQuery().exec(str);
    if (bOk)
    {
        qDebug()<<"exec ok: ";
        while(SqliteEx::getClass().getQuery().next())
        {
            qDebug()<<"id: "<< SqliteEx::getClass().getQuery().value("id").toInt();
            qDebug()<<"name: "<< SqliteEx::getClass().getQuery().value("name").toString();
            qDebug()<<"score: "<< SqliteEx::getClass().getQuery().value("score").toInt();
            qDebug()<<"class: "<< SqliteEx::getClass().getQuery().value("class").toString()<<endl;
        }
    } else {
        qDebug()<<"exec fail: "<<SqliteEx::getClass().getDatabase().lastError().text();
    }
}

void MainWindow::testMysql()
{
    INI_DB_ST st;
    st.strDatabaseName = "mysql";
    st.strHostName = "localhost";
    st.strUserName = "root";
    st.strPassword = "abc123456";

    if(MySqlEx::getClass().initDb(st))
    {
        qDebug()<<"Success to init db mysql!";
    } else {
        qDebug()<<"Failed to init db: "<<MySqlEx::getClass().getDatabase().lastError().text();
        return;
    }
}

void MainWindow::testOdbc()
{
    INI_DB_ST st;
    st.strDatabaseName = "my.db";
    st.strHostName = "";
    st.strUserName = "";
    st.strPassword = "";

    if(OdbcEx::getClass().initDb(st))
    {
        qDebug()<<"Success to init db mysql!";
    } else {
        qDebug()<<"Failed to init db: "<<OdbcEx::getClass().getDatabase().lastError().text();
        return;
    }
}
void MainWindow::testPsql()
{
    INI_DB_ST st;
    st.strDatabaseName = "my.db";
    st.strHostName = "";
    st.strUserName = "";
    st.strPassword = "";

    if(PsqlEx::getClass().initDb(st))
    {
        qDebug()<<"Success to init db mysql!";
    } else {
        qDebug()<<"Failed to init db: "<<PsqlEx::getClass().getDatabase().lastError().text();
        return;
    }
}

void MainWindow::on_pushButton_file_clicked()
{
    QString str ="D:\\test\\a.xlsx";
    qDebug()<<FileEx::allFiles("D:\\test");
    qDebug()<<FileEx::fileSize2String(QFileInfo(str).size());
    qDebug()<<FileEx::getHash(str);
    str = "D:\\DevelopTool\\Qt\\qt-opensource-windows-x86-5.12.10.exe";
    qDebug()<<FileEx::fileSize2String(QFileInfo(str).size());
    qDebug()<<FileEx::getHash(str);

}

void MainWindow::on_pushButton_time_clicked()
{
    qDebug()<<TimeEx::YYYY_MM_DD_HH_MM_SS();
    TimeEx::blockTime(1000*10);
    qDebug()<<TimeEx::YYYY_MM_DD_HH_MM_SS_ZZZ();
}

void MainWindow::on_pushButton_os_clicked()
{
    qDebug()<<QLocale::system().name();
    qDebug()<<SystemEx::systemName();
    qDebug()<<SystemEx::hostName();

    qDebug()<<"getDiskFreeSpace app: "<<SystemEx::getDiskFreeSpace(QCoreApplication::applicationDirPath());
    qDebug()<<"getDiskFreeSpace C: "<<SystemEx::getDiskFreeSpace("C:/");
    qDebug()<<"getDiskSpace C: "<<SystemEx::getDiskSpace("C:") / (1024*1024*1024);
    qDebug()<<"getDiskFreeSpace D: "<<SystemEx::getDiskFreeSpace("D:\\");
    qDebug()<<"getDiskSpace D: "<<SystemEx::getDiskSpace("D:") / (1024*1024*1024);
    qDebug()<<"getDiskFreeSpace E: "<<SystemEx::getDiskFreeSpace("E:");

    QString strErrMsg;
    QList<qint64> lstPid;
    SystemEx::isProcessRunningByFilename("D:\\Code\\Go\\src\\github.com\\pjh130\\qt\\Core\\AaaTestCore\\release\\AaaTestCore.exe", strErrMsg, lstPid, true);
    qDebug()<<"strErrMsg: "<<strErrMsg;
    qDebug()<<"lstPid: "<<lstPid;
}

void MainWindow::on_pushButton_string_clicked()
{

}

void MainWindow::on_pushButton_textcodec_clicked()
{

}

void MainWindow::on_pushButton_image_clicked()
{
    QString strSrc = "D:\\test\\matebook.png";
    QString strDec = "D:\\test\\new\\matebook.png";
    qDebug()<<"toGrayImge: "<<ImageEx::toGrayImge(strSrc, strDec);
}

void MainWindow::on_pushButton_settings_clicked()
{
    QString strPath = QCoreApplication::applicationDirPath() + QDir::separator() + "ini";
    strPath = strPath + QDir::separator() + "setting.ini";
    QString strGroup = "user1";
    QString strName = "zhangsan";
    QString strValue = "1234567";
    SettingsEx::setValue(strPath, strGroup, strName, strValue);
    qDebug()<<SettingsEx::getValue(strPath, strGroup, strName);

    strGroup = "user2";
    strName = "lisi";
    strValue = "654321";
    SettingsEx::setValue(strPath, strGroup, strName, strValue);
    qDebug()<<SettingsEx::getValue(strPath, strGroup, strName);

    SettingsEx::removeValue(strPath, strGroup, strName);
}
