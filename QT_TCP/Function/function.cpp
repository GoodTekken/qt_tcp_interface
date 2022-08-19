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

QByteArray convertUInt32ToByte(uint32_t data)
{
    QByteArray array;
    array.clear();
    array.append(data & 0x000000FF);
    array.append(data & 0x0000FF00);
    array.append(data & 0x0000FF00);
    array.append(data & 0xFF000000);
    return array;
}

QByteArray convertUInt16ToByte(uint16_t data)
{
    QByteArray array;
    array.clear();
    array.append(data & 0x00FF);
    array.append(data & 0xFF00);
    return array;
}
