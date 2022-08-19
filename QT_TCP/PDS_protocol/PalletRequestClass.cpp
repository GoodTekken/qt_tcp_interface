#include "PDS_protocol/PalletRequestClass.h"
#include "Function/function.h"
#include <QDebug>

#define qtcout qDebug()<<"["<<__FILE__<<":"<<__LINE__<<"]"

PalletRequestClass::PalletRequestClass()
{

};
PalletRequestClass::~PalletRequestClass()
{

};
PalletRequestClass::PalletRequestClass(uint32_t commandID, uint16_t palletType)
{
    palletRequestStruct.startSequnce[0] = 0x73;//73 74 61 72
    palletRequestStruct.startSequnce[1] = 0x74;
    palletRequestStruct.startSequnce[2] = 0x61;
    palletRequestStruct.startSequnce[3] = 0x72;

    palletRequestStruct.commandID = commandID;
    palletRequestStruct.argsLen = 7;
    palletRequestStruct.palletType = palletType;
    palletRequestStruct.depthHint = -1;
    palletRequestStruct.filterMask = 0;

    palletRequestStruct.stopSequence[0] = 0x73;//73 74 6f 70 0d 0a
    palletRequestStruct.stopSequence[1] = 0x74;
    palletRequestStruct.stopSequence[2] = 0x6f;
    palletRequestStruct.stopSequence[3] = 0x70;
    palletRequestStruct.stopSequence[4] = 0x0d;
    palletRequestStruct.stopSequence[5] = 0x0a;
};

QByteArray PalletRequestClass::ToArray()
{
    QByteArray array;
    array.clear();
    array.append((char*)&palletRequestStruct,sizeof(palletRequestStruct));
    return array;
}
void PalletRequestClass::ToString()
{

};
