#include "sqliteex.h"

SqliteEx::SqliteEx():DbBase()
{

}

SqliteEx::~SqliteEx()
{

}

SqliteEx & SqliteEx::getClass()
{
    static SqliteEx s;
    return s;
}

bool SqliteEx::initDb(const INI_DB_ST &init)
{
    //如果初始化过就不需要初始化了
    if(isInitOK())
    {
        return true;
    }

    //设置配置
    setInit(init);

    QString strDir = QCoreApplication::applicationDirPath() + "/db";
    QDir dir(strDir);
    if(!dir.exists())
    {
        dir.mkdir(strDir);
    }

    getDatabase() = QSqlDatabase::addDatabase("QSQLITE");
    if (!getInit().strHostName.isEmpty())
    {
        getDatabase().setHostName(getInit().strHostName);
    }
    if (!getInit().strDatabaseName.isEmpty())
    {
        getDatabase().setDatabaseName(getInit().strDatabaseName);       //这里输入你的数据库名
    }
    if (!getInit().strUserName.isEmpty())
    {
        getDatabase().setUserName(getInit().strUserName);
    }
    if (!getInit().strPassword.isEmpty())
    {
        getDatabase().setPassword(getInit().strPassword);   //这里输入你的密码
    }

    //如果本目录下没有该文件,则会在本目录下生成,否则连接该文件
    getDatabase().setDatabaseName(strDir + "/" + getInit().strDatabaseName);
    if (!getDatabase().open())
    {
        setInitOK(false);
    } else {
        //打开成功
        getQuery() = QSqlQuery(getDatabase());
        setInitOK(true);
    }

    return isInitOK();
}
