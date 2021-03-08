#include "odbcex.h"

OdbcEx::OdbcEx():DbBase()
{

}

OdbcEx::~OdbcEx()
{

}

OdbcEx & OdbcEx::getClass()
{
    static OdbcEx s;
    return s;
}

bool OdbcEx::initDb(const INI_DB_ST &init)
{
    //如果初始化过就不需要初始化了
    if(isInitOK())
    {
        return true;
    }

    //设置配置
    setInit(init);

    getDatabase() = QSqlDatabase::addDatabase("QODBC");

    QString dsn = QString("DRIVER={SQL SERVER};SERVER=%1;DATABASE=%2;")
        .arg(getInit().strHostName).arg(getInit().strDatabaseName);
    getDatabase().setDatabaseName(dsn);
    getDatabase().setUserName(getInit().strUserName);
    getDatabase().setPassword(getInit().strPassword);

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

