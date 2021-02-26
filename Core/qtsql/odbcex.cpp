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

bool OdbcEx::initDb(INI_DB_ST init)
{
    //如果初始化过就不需要初始化了
    if(isInitOK())
    {
        return true;
    }

    //设置配置
    setInit(init);

    getDatabase() = QSqlDatabase::addDatabase("QODBC");
//    getDatabase().setHostName(getInit().strHostName);
//    getDatabase().setDatabaseName(getInit().strDatabaseName);       //这里输入你的数据库名
//    getDatabase().setUserName(getInit().strUserName);
//    getDatabase().setPassword(getInit().strPassword);   //这里输入你的密码
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

