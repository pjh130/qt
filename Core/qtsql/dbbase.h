#ifndef DBBASE_H
#define DBBASE_H

#include <QtCore>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>

typedef struct
{
    QString strHostName;
    QString strDatabaseName;
    QString strUserName;
    QString strPassword;
}INI_DB_ST;

class DbBase
{
public:
    DbBase();
    ~DbBase();

    //在子类中必须要实现的接口
    virtual bool initDb(INI_DB_ST init) = 0;

    void setInit(INI_DB_ST init);
    INI_DB_ST & getInit();

    QSqlDatabase & getDatabase();
    QSqlQuery & getQuery();

    bool isInitOK();
    void setInitOK(bool bOk);

    void closeDB();

private:


private:
    INI_DB_ST m_init;
    QSqlDatabase m_database;
    QSqlQuery m_query;
    bool m_bInitDB;
};

#endif // DBBASE_H
