#include "AGV_Message.h"

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
