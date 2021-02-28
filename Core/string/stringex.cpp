#include "stringex.h"

StringEx::StringEx()
{

}

StringEx::~StringEx()
{

}

QByteArray StringEx::first(QByteArray& str, const QByteArray& split)
{
    QByteArray ret;
    int endOf = str.indexOf(split);
    if ( endOf == 0 )
    {
        str.remove(0, 1);
    }
    else
    if ( endOf > 0 )
    {
        ret = str.left(endOf);
        str.remove(0, endOf +1);
    }
    else
    {
        ret = str;
    }

    return ret;
}
