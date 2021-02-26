#ifndef ODBCEX_H
#define ODBCEX_H

#include "dbbase.h"

class OdbcEx: public DbBase
{
public:
    OdbcEx();
    ~OdbcEx();

    static OdbcEx & getClass(); //返回对象引用，是单例类
    bool initDb(INI_DB_ST init);

private:

public slots:

signals:

protected:

private:

};

#endif // ODBCEX_H
