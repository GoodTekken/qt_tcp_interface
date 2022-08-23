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

//小端读取
template <typename T> // T must be integer type
T to_little_endian(T x)
{
    size_t n = sizeof(T) / sizeof(char); // 2,4,8

    T res;
    char* p = (char*)&res;
    T mask = static_cast<T>(0xFF);

    for (size_t i = 0; i < n; i++)
    {
        int offset = 8 * i;
        p[i] = (x & (mask << offset)) >> offset;
    }

    return res;
}

//大端读取
template <typename T> // T must be integer type
T to_large_endian(T x)
{
    size_t n = sizeof(T) / sizeof(char); // 2,4,8

    T res;
    char* p = (char*)&res;
    T mask = static_cast<T>(0xFF);

    for (size_t i = 0; i < n; i++)
    {
        int offset = 8 * (n - i - 1);
        p[i] = (x & (mask << offset)) >> offset;
    }

    return res;
}


uint16_t swapUInt16(uint16_t value)
{
    return ((value & 0x00FF) << 8) |
           ((value & 0xFF00) >> 8);
}

uint32_t swapUInt32(uint32_t value)
{
    return ((value & 0x000000FF) << 24) |
           ((value & 0x0000FF00) << 8) |
           ((value & 0x00FF0000) >> 8) |
           ((value & 0xFF000000) >> 24);
}


int32_t swapInt32(int32_t value)
{
    int a = value;
    return ((value & 0x000000FF) << 24) |
           ((value & 0x0000FF00) << 8) |
           ((value & 0x00FF0000) >> 8) |
           ((value & 0xFF000000) >> 24);
}

float Byte2Float(QByteArray byte)
{
    float result = 0;
    int size = byte.size();
    char* data_char = byte.data();
    char* p = (char*)&result;
    for(int index = 0; index < size; index++)
        {
        *(p + index) = *(data_char + size - 1 - index);
        }
    return result;
}

void reverseByte(QByteArray &arrayToChange,uint32_t start,uint32_t end){
    //the end will be swap too
    //you should offer a close interval
    assert(start<=end);
    char byte;
    for (uint32_t i=start;i<=(start+end)/2;i++) {
        byte=arrayToChange[i];
        arrayToChange[start+i]=arrayToChange[end-i];
        arrayToChange[end-i]=byte;
    }



}
