#include "pdsPalletResponseClass.h"
#include "Function/function.h"
#include <cstring>
#include <iostream>
#include <QDebug>

pdsPalletResponseClass::pdsPalletResponseClass()
{
    ;
}

pdsPalletResponseClass::~pdsPalletResponseClass()
{
    ;
}

void pdsPalletResponseClass::response_failure(uint32_t commandID,int32_t errorCode)
{
    palletResponseFailureStruct.startSequnce[0] = 0x73;//73 74 61 72
    palletResponseFailureStruct.startSequnce[1] = 0x74;
    palletResponseFailureStruct.startSequnce[2] = 0x61;
    palletResponseFailureStruct.startSequnce[3] = 0x72;

    palletResponseFailureStruct.commandID = commandID;
    palletResponseFailureStruct.errorCode = errorCode;
    palletResponseFailureStruct.len = 6;

    palletResponseFailureStruct.stopSequence[0] = 0x73;//73 74 6f 70 0d 0a
    palletResponseFailureStruct.stopSequence[1] = 0x74;
    palletResponseFailureStruct.stopSequence[2] = 0x6f;
    palletResponseFailureStruct.stopSequence[3] = 0x70;
    palletResponseFailureStruct.stopSequence[4] = 0x0d;
    palletResponseFailureStruct.stopSequence[5] = 0x0a;
}

QByteArray pdsPalletResponseClass::ToFailureArray()
{
    palletResponseFailureStruct.commandID = swapUInt32(palletResponseFailureStruct.commandID);
    palletResponseFailureStruct.errorCode = swapInt32(palletResponseFailureStruct.errorCode);
    palletResponseFailureStruct.len = swapUInt32(palletResponseFailureStruct.len);

    QByteArray array;
    array.clear();
    unsigned char buf[22];
    std::memcpy(buf,(char*)&palletResponseFailureStruct,sizeof(palletResponseFailureStruct));
    for(int i= 0;i<22;i++)
    {
        array.append(buf[i]);
    }
    return array;
}

pdsPalletResponseClass::pdsPalletResponseClass(QByteArray array)
{
    int count = array.count();
    if(count == 22)
    {
        getPalletResponse_failure* data = (getPalletResponse_failure*)array.data();
        data->commandID = swapUInt32(data->commandID);
        data->errorCode = swapInt32(data->errorCode);
        data->len = swapUInt32(data->len);
        palletResponseFailureStruct.startSequnce[0] = data->startSequnce[0];
        palletResponseFailureStruct.startSequnce[1] = data->startSequnce[1];
        palletResponseFailureStruct.startSequnce[2] = data->startSequnce[2];
        palletResponseFailureStruct.startSequnce[3] = data->startSequnce[3];
        palletResponseFailureStruct.commandID = data->commandID;
        palletResponseFailureStruct.errorCode = data->errorCode;
        palletResponseFailureStruct.len = data->len;
        palletResponseFailureStruct.stopSequence[0] = data->stopSequence[0];
        palletResponseFailureStruct.stopSequence[1] = data->stopSequence[1];
        palletResponseFailureStruct.stopSequence[2] = data->stopSequence[2];
        palletResponseFailureStruct.stopSequence[3] = data->stopSequence[3];
        palletResponseFailureStruct.stopSequence[4] = data->stopSequence[4];
        palletResponseFailureStruct.stopSequence[5] = data->stopSequence[5];
    }
}

void pdsPalletResponseClass::ToString()
{

};
