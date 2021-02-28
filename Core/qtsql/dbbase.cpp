#include "dbbase.h"

DbBase::DbBase()
{
    m_bInitDB = false;
}

DbBase::~DbBase()
{
    closeDB();
}

void DbBase::closeDB()
{
    if (m_database.isOpen())
    {
      m_database.close();
    }
}

void DbBase::setInit(INI_DB_ST init)
{
    m_init.strHostName = init.strHostName;
    m_init.strDatabaseName = init.strDatabaseName;
    m_init.strUserName = init.strUserName;
    m_init.strPassword = init.strPassword;
}

QStringList DbBase::tables()
{
    return m_database.tables();
}

bool DbBase::isInitOK()
{
    return m_bInitDB;
}

void DbBase::setInitOK(bool bOk)
{
    m_bInitDB = bOk;
}

QSqlDatabase & DbBase::getDatabase()
{
    return m_database;
}

QSqlQuery & DbBase::getQuery()
{
    return m_query;
}

INI_DB_ST & DbBase::getInit()
{
    return m_init;
}


