#include "PDS_protocol/pdsPalletRequestClass.h"
#include "Function/function.h"
#include <cstring>
#include <iostream>
#include <QDebug>

#define qtcout qDebug()<<"["<<__FILE__<<":"<<__LINE__<<"]"

pdsPalletRequestClass::pdsPalletRequestClass()
{

};

pdsPalletRequestClass::~pdsPalletRequestClass()
{

};

pdsPalletRequestClass::pdsPalletRequestClass(uint32_t commandID, uint16_t palletType)
{
    strncpy(palletRequestStruct.startSequnce,seqStart,4);
    palletRequestStruct.commandID = commandID;
    palletRequestStruct.argsLen = 7;
    palletRequestStruct.palletType = palletType;
    palletRequestStruct.depthHint = 1.2;
    palletRequestStruct.filterMask = 0;
    strncpy(palletRequestStruct.stopSequence,seqEnd,6);
};

QByteArray pdsPalletRequestClass::ToArray()
{
    palletRequestStruct.commandID = swapUInt32(palletRequestStruct.commandID);
    palletRequestStruct.argsLen = swapUInt32(palletRequestStruct.argsLen);
    palletRequestStruct.palletType = swapUInt16(palletRequestStruct.palletType);
    //palletRequestStruct.depthHint = swapInt32(palletRequestStruct.depthHint);

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

pdsPalletRequestClass::pdsPalletRequestClass(QByteArray array)
{
    getPalletRequest* data = (getPalletRequest*)array.data();
    data->commandID=swapUInt32(data->commandID);
    data->argsLen=swapUInt32(data->argsLen);
    data->palletType =swapUInt16(data->palletType);

    QByteArray depthArray;
    depthArray.append(array[14]);
    depthArray.append(array[15]);
    depthArray.append(array[16]);
    depthArray.append(array[17]);
    data->depthHint = Byte2Float(depthArray);//data->depthHint unstable,  can not be used.

    strncpy(palletRequestStruct.startSequnce,data->startSequnce,4);
    palletRequestStruct.commandID =data->commandID;
    palletRequestStruct.argsLen   =data->argsLen;
    palletRequestStruct.palletType =data->palletType;
    palletRequestStruct.depthHint = Byte2Float(depthArray);
    palletRequestStruct.filterMask =data->filterMask;
    strncpy(palletRequestStruct.stopSequence,data->stopSequence,4);
}

void pdsPalletRequestClass::ToString()
{

};
