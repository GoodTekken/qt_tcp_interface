#include "pdsVolCheckResponseClass.h"
#include "Function/function.h"

volCheckResponse volCheckResponseStruct;
pdsVolCheckResponseClass::pdsVolCheckResponseClass()
{

}

pdsVolCheckResponseClass::~pdsVolCheckResponseClass()
{

}
pdsVolCheckResponseClass::pdsVolCheckResponseClass(int errorCode,int Npix)    //Number of pixels in the VOI
{
    strncpy(volCheckResponseStruct.startSequnce,seqStart,4);
    volCheckResponseStruct.commandID=5;
    volCheckResponseStruct.errorCode=errorCode;
    volCheckResponseStruct.len=8;
    volCheckResponseStruct.elapsedTime = -1.254;
    volCheckResponseStruct.Npix = Npix;
    strncpy(volCheckResponseStruct.stopSequence,seqEnd,6);
}
QByteArray pdsVolCheckResponseClass::ToArray()
{
    volCheckResponseStruct.commandID = swapUInt32(volCheckResponseStruct.commandID);
    volCheckResponseStruct.errorCode = swapInt32(volCheckResponseStruct.errorCode);
    volCheckResponseStruct.len = swapUInt32(volCheckResponseStruct.len);
    volCheckResponseStruct.Npix = swapInt32(volCheckResponseStruct.Npix);

    QByteArray array;
    array.clear();
    array.append((char*)&volCheckResponseStruct,sizeof(volCheckResponseStruct));
    reverseByte(array,16,16+3);

    return array;
}


pdsVolCheckResponseClass::pdsVolCheckResponseClass(QByteArray array)
{
    volCheckResponse* data = (volCheckResponse*)array.data();
    data->commandID=swapUInt32(data->commandID);
    data->errorCode=swapInt32(data->errorCode);
    data->len=swapUInt32(data->len);
    data->Npix=swapInt32(data->Npix);

    strncpy(volCheckResponseStruct.startSequnce,data->startSequnce,4);
    volCheckResponseStruct.commandID =data->commandID;
    volCheckResponseStruct.errorCode   =data->errorCode;
    volCheckResponseStruct.len   =data->len;
    volCheckResponseStruct.Npix   =data->Npix;
    volCheckResponseStruct.elapsedTime =byte2Float(array,16);
    strncpy(volCheckResponseStruct.stopSequence,data->stopSequence,6);
}
