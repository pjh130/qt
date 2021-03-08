#ifndef SQLITEEX_H
#define SQLITEEX_H

#include "dbbase.h"

class SqliteEx : public DbBase
{
public:
    SqliteEx();
    ~SqliteEx();

    static SqliteEx & getClass(); //返回对象引用，是单例类
    bool initDb(const INI_DB_ST &init);

private:

public slots:

signals:

protected:

private:

};

#endif // SQLITEEX_H
