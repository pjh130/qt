#ifndef MYSQLEX_H
#define MYSQLEX_H

#include "dbbase.h"

class MySqlEx: public DbBase
{
public:
    MySqlEx();
    ~MySqlEx();

    static MySqlEx & getClass(); //返回对象引用，是单例类
    bool initDb(INI_DB_ST init);

private:

public slots:

signals:

protected:

private:

};

#endif // MYSQLEX_H
