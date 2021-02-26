#ifndef PSQLEX_H
#define PSQLEX_H
#include"dbbase.h"

class PsqlEx: public DbBase
{
public:
    PsqlEx();
    ~PsqlEx();

    static PsqlEx & getClass(); //返回对象引用，是单例类
    bool initDb(INI_DB_ST init);

private:

public slots:

signals:

protected:

private:

};

#endif // PSQLEX_H
