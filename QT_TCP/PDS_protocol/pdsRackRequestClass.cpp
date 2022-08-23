#include "pdsRackRequestClass.h"
#include "Function/function.h"

pdsRackRequestClass::pdsRackRequestClass()
{

}

pdsRackRequestClass::~pdsRackRequestClass()
{

}

pdsRackRequestClass::pdsRackRequestClass(uint32_t commandID, float depthHint)
{
    strncpy(rackRequestStruct.startSequnce,seqStart,4);
    rackRequestStruct.commandID = commandID;
    rackRequestStruct.argsLen = 24;
    rackRequestStruct.horizontalDropPos =1;
    rackRequestStruct.verticalDropPos = 2;
    rackRequestStruct.cameraPos = 3;
    rackRequestStruct.depthHint = depthHint;
    rackRequestStruct.zHint = 1.1;
    rackRequestStruct.clearingDepth = 2.2;
    rackRequestStruct.clearingWidth =3.3;
    rackRequestStruct.clearingHeight =4.4;
    rackRequestStruct.strayLightFilter =5;
    strncpy(rackRequestStruct.stopSequence,seqEnd,6);
}

pdsRackRequestClass::pdsRackRequestClass(QByteArray array)
{
    getRackRequest* data = (getRackRequest*)array.data();
    data->commandID=swapUInt32(data->commandID);
    data->argsLen=swapUInt32(data->argsLen);

    strncpy(rackRequestStruct.startSequnce,data->startSequnce,4);
    rackRequestStruct.commandID =data->commandID;
    rackRequestStruct.argsLen   =data->argsLen;
    rackRequestStruct.horizontalDropPos =data->horizontalDropPos;
    rackRequestStruct.verticalDropPos = data->verticalDropPos;
    rackRequestStruct.cameraPos = data->cameraPos;
    rackRequestStruct.depthHint = byte2Float(array,15);
    rackRequestStruct.zHint = byte2Float(array,19);
    rackRequestStruct.clearingDepth = byte2Float(array,23);
    rackRequestStruct.clearingWidth =byte2Float(array,27);
    rackRequestStruct.clearingHeight =byte2Float(array,31);
    rackRequestStruct.strayLightFilter =data->strayLightFilter;
    strncpy(rackRequestStruct.stopSequence,data->stopSequence,6);
}

QByteArray pdsRackRequestClass::ToArray()
{
    rackRequestStruct.commandID = swapUInt32(rackRequestStruct.commandID);
    rackRequestStruct.argsLen = swapUInt32(rackRequestStruct.argsLen);

    QByteArray array;
    array.clear();
    array.append((char*)&rackRequestStruct,sizeof(rackRequestStruct));
    reverseByte(array,15,18);
    reverseByte(array,19,22);
    reverseByte(array,23,26);
    reverseByte(array,27,30);
    reverseByte(array,31,34);

    return array;
}

void pdsRackRequestClass::ToString()
{

}
