#include "pdsVolCheckRequestClass.h"
#include "Function/function.h"

pdsVolCheckRequestClass::pdsVolCheckRequestClass()
{
    ;
}

pdsVolCheckRequestClass::~pdsVolCheckRequestClass()
{
    ;
}

pdsVolCheckRequestClass::pdsVolCheckRequestClass(pds_point min,pds_point max)
{
    strncpy(volCheckRequestStruct.startSequnce,seqStart,4);
    volCheckRequestStruct.commandID = 5;
    volCheckRequestStruct.argsLen = 25;
    volCheckRequestStruct.xmin = min.x;
    volCheckRequestStruct.xmax = max.x;
    volCheckRequestStruct.ymin = min.y;
    volCheckRequestStruct.ymax = max.y;
    volCheckRequestStruct.zmin = min.z;
    volCheckRequestStruct.zmax = max.z;
    volCheckRequestStruct.strayLightFilter =30;
    strncpy(volCheckRequestStruct.stopSequence,seqEnd,6);
}

QByteArray pdsVolCheckRequestClass::ToArray()
{
    volCheckRequestStruct.commandID = swapUInt32(volCheckRequestStruct.commandID);
    volCheckRequestStruct.argsLen = swapUInt32(volCheckRequestStruct.argsLen);

    QByteArray array;
    array.clear();
    array.append((char*)&volCheckRequestStruct,sizeof(volCheckRequestStruct));
    reverseByte(array,12,15);
    reverseByte(array,16,19);
    reverseByte(array,20,23);
    reverseByte(array,24,27);
    reverseByte(array,28,31);
    reverseByte(array,32,35);
    return array;
}
pdsVolCheckRequestClass::pdsVolCheckRequestClass(QByteArray array)
{
    volCheckRequest* data = (volCheckRequest*)array.data();
    data->commandID=swapUInt32(data->commandID);
    data->argsLen=swapUInt32(data->argsLen);

    strncpy(volCheckRequestStruct.startSequnce,data->startSequnce,4);
    volCheckRequestStruct.commandID =data->commandID;
    volCheckRequestStruct.argsLen   =data->argsLen;
    volCheckRequestStruct.xmin = byte2Float(array,12);
    volCheckRequestStruct.xmax = byte2Float(array,16);
    volCheckRequestStruct.ymin = byte2Float(array,20);
    volCheckRequestStruct.ymax =byte2Float(array,24);
    volCheckRequestStruct.zmin =byte2Float(array,28);
    volCheckRequestStruct.zmax =byte2Float(array,32);
    volCheckRequestStruct.strayLightFilter =data->strayLightFilter;
    strncpy(volCheckRequestStruct.stopSequence,data->stopSequence,6);
}
