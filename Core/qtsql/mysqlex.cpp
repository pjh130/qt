#include "mysqlex.h"

MySqlEx::MySqlEx():DbBase()
{

}

MySqlEx::~MySqlEx()
{

}

MySqlEx & MySqlEx::getClass()
{
    static MySqlEx s;
    return s;
}

bool MySqlEx::initDb(const INI_DB_ST &init)
{
    //如果初始化过就不需要初始化了
    if(isInitOK())
    {
        return true;
    }

    //设置配置
    setInit(init);

    getDatabase() = QSqlDatabase::addDatabase("QMYSQL");
    getDatabase().setHostName(getInit().strHostName);
    getDatabase().setDatabaseName(getInit().strDatabaseName);       //这里输入你的数据库名
    getDatabase().setUserName(getInit().strUserName);
    getDatabase().setPassword(getInit().strPassword);   //这里输入你的密码
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
