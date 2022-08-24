#include "pdsGetConfigRequestClass.h"
#include "Function/function.h"

pdsGetConfigRequestClass::pdsGetConfigRequestClass()
{
    strncpy(getConfigRequestStruct.startSequnce,seqStart,4);
    getConfigRequestStruct.commandID = 7;
    getConfigRequestStruct.argsLen = 0;
    strncpy(getConfigRequestStruct.stopSequence,seqEnd,6);
}

pdsGetConfigRequestClass::~pdsGetConfigRequestClass()
{
    ;
}

QByteArray pdsGetConfigRequestClass::ToArray()
{
    getConfigRequestStruct.commandID = swapUInt32(getConfigRequestStruct.commandID);
    getConfigRequestStruct.argsLen = swapUInt32(getConfigRequestStruct.argsLen);
    QByteArray array;
    array.clear();
    array.append((char*)&getConfigRequestStruct,sizeof(getConfigRequestStruct));
    return array;
}

pdsGetConfigRequestClass::pdsGetConfigRequestClass(QByteArray array)
{
    getConfigRequest* data = (getConfigRequest*)array.data();
    data->commandID=swapUInt32(data->commandID);
    data->argsLen=swapUInt32(data->argsLen);

    strncpy(getConfigRequestStruct.startSequnce,data->startSequnce,4);
    getConfigRequestStruct.commandID =data->commandID;
    getConfigRequestStruct.argsLen   =data->argsLen;
    strncpy(getConfigRequestStruct.stopSequence,data->stopSequence,6);
}
