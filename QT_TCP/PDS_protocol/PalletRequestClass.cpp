#include "PDS_protocol/PalletRequestClass.h"
#include "Function/function.h"
#include <cstring>
#include <iostream>
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
    palletRequestStruct.depthHint = 1.2;
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
    palletRequestStruct.commandID = swapUInt32(palletRequestStruct.commandID);
    palletRequestStruct.argsLen = swapUInt32(palletRequestStruct.argsLen);
    palletRequestStruct.palletType = swapUInt16(palletRequestStruct.palletType);
    palletRequestStruct.depthHint = swapInt32(palletRequestStruct.depthHint);

    QByteArray array;
    array.clear();
    unsigned char buf[25];
    std::memcpy(buf,(char*)&palletRequestStruct,sizeof(palletRequestStruct));
    for(int i= 0;i<14;i++)
    {
        array.append(buf[i]);
    }
    array.append(buf[17]);
    array.append(buf[16]);
    array.append(buf[15]);
    array.append(buf[14]);
    for(int i= 18;i<25;i++)
    {
        array.append(buf[i]);
    }
    //array.append((char*)&palletRequestStruct,sizeof(palletRequestStruct));
    return array;
}

PalletRequestClass::PalletRequestClass(QByteArray array)
{
    getPalletRequest *data = (getPalletRequest*)array.data();
    data->commandID=swapUInt32(data->commandID);
    data->argsLen=swapUInt32(data->argsLen);
    data->palletType =swapUInt16(data->palletType);

    QByteArray depthArray;
    depthArray.append(array[14]);
    depthArray.append(array[15]);
    depthArray.append(array[16]);
    depthArray.append(array[17]);
//    data->depthHint = Byte2Float(depthArray);//data->depthHint unstable,  can not be used.
    depthHint = Byte2Float(depthArray);
    qDebug("%f",data->depthHint);
}

void PalletRequestClass::ToString()
{

};
