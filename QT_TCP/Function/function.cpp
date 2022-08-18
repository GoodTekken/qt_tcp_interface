#include "function.h"

void string_to_hex(QString hex,QByteArray &qbyte)
{
    hex=hex.trimmed();
    QStringList sl=hex.split(" ");
    foreach(QString s,sl)
    {
        if(!s.isEmpty())
        {
            qbyte.append((char)s.toInt(0,16)&0xFF);
        }
    }

}
