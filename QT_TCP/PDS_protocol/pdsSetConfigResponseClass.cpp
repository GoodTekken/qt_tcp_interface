#include "pdsSetConfigResponseClass.h"
#include "Function/function.h"

pdsSetConfigResponseClass::pdsSetConfigResponseClass()
{
    strncpy(setConfigResponseStruct.startSequnce,seqStart,4);
    setConfigResponseStruct.commandID = 8;
    setConfigResponseStruct.errorCode = 1001;
    setConfigResponseStruct.len = 0;
    strncpy(setConfigResponseStruct.stopSequence,seqEnd,6);
}

pdsSetConfigResponseClass::~pdsSetConfigResponseClass()
{
    ;
}

QByteArray pdsSetConfigResponseClass::ToArray()
{
    setConfigResponseStruct.commandID = swapUInt32(setConfigResponseStruct.commandID);
    setConfigResponseStruct.errorCode = swapInt32(setConfigResponseStruct.errorCode);
    setConfigResponseStruct.len = swapUInt32(setConfigResponseStruct.len);
    QByteArray array;
    array.clear();
    array.append((char*)&setConfigResponseStruct,sizeof(setConfigResponseStruct));
    return array;
}

pdsSetConfigResponseClass::pdsSetConfigResponseClass(QByteArray array)
{
    setConfigResponse* data = (setConfigResponse*)array.data();
    data->commandID=swapUInt32(data->commandID);
    data->errorCode=swapInt32(data->errorCode);
    data->len=swapUInt32(data->len);

    strncpy(setConfigResponseStruct.startSequnce,data->startSequnce,4);
    setConfigResponseStruct.commandID =data->commandID;
    setConfigResponseStruct.errorCode =data->errorCode;
    setConfigResponseStruct.len   =data->len;
    strncpy(setConfigResponseStruct.stopSequence,data->stopSequence,6);
}
