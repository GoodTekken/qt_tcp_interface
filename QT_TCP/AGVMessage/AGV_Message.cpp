#include "AGV_Message.h"


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


uint16_t swapInt16(uint16_t value)
{
    return ((value & 0x00FF) << 8) |
           ((value & 0xFF00) >> 8);
}

uint32_t swapInt32(uint32_t value)
{
    return ((value & 0x000000FF) << 24) |
           ((value & 0x0000FF00) << 8) |
           ((value & 0x00FF0000) >> 8) |
           ((value & 0xFF000000) >> 24);
}


int Crc16(byte* px, int usLen)
{
    /* int result;
    BYTE high,low;*/
    int i = 0;
    byte ucCRCHi = 0xFF;
    byte ucCRCLo = 0xFF;
    int iIndex = 0x0000;
    while (usLen--)
    {
        iIndex = (int)(ucCRCLo ^ px[i++]);
        ucCRCLo = (byte)(ucCRCHi ^ auchCRCHi[iIndex]);
        ucCRCHi = auchCRCLo[iIndex];
    }
    return (ucCRCHi << 8 | ucCRCLo);
}


unsigned int Crc16(byte* px, int startIndex,int usLen)
{
    /* int result;
    BYTE high,low;*/
    int i = startIndex;
    byte ucCRCHi = 0xFF;
    byte ucCRCLo = 0xFF;
    int iIndex = 0x0000;
    while (usLen--)
    {
        iIndex = (int)(ucCRCLo ^ px[i++]);
        ucCRCLo = (byte)(ucCRCHi ^ auchCRCHi[iIndex]);
        ucCRCHi = auchCRCLo[iIndex];
    }
    return (ucCRCHi << 8 | ucCRCLo);
}
