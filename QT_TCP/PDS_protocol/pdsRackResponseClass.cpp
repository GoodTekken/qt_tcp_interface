#include "pdsRackResponseClass.h"
#include "Function/function.h"

pdsRackResponseClass::pdsRackResponseClass()
{

}
pdsRackResponseClass::~pdsRackResponseClass()
{

}

void pdsRackResponseClass::response_failure(uint32_t commandID,int32_t errorCode)
{
    strncpy(rackResponseFailureStruct.startSequnce,seqStart,4);
    rackResponseFailureStruct.commandID = commandID;
    rackResponseFailureStruct.errorCode = errorCode;
    rackResponseFailureStruct.len = 6;
    strncpy(rackResponseFailureStruct.stopSequence,seqEnd,6);
}
QByteArray pdsRackResponseClass::ToFailureArray()
{
    rackResponseFailureStruct.commandID = swapUInt32(rackResponseFailureStruct.commandID);
    rackResponseFailureStruct.errorCode = swapInt32(rackResponseFailureStruct.errorCode);
    rackResponseFailureStruct.len = swapUInt32(rackResponseFailureStruct.len);

    QByteArray array;
    array.clear();
    array.append((char*)&rackResponseFailureStruct,sizeof(rackResponseFailureStruct));
    return array;
}

void pdsRackResponseClass::response_success(pdsRackCoordinateClass rackCoordinate)
{
    strncpy(rackResponseSuccessStruct.startSequnce,seqStart,4);
    rackResponseSuccessStruct.commandID = 4;
    rackResponseSuccessStruct.errorCode = 0;
    rackResponseSuccessStruct.len = 43;      //37+6
    rackResponseSuccessStruct.elapsedTime = rackCoordinate.elapsedTime;          //4 byte  (Elapsed time (sec) of the detection)
    rackResponseSuccessStruct.confidence = rackCoordinate.confidence;            //4 byte  (Average correlation score of the segmented pallet pockets against the pocket-type kernel.)
    rackResponseSuccessStruct.X = rackCoordinate.X;                              //4 byte  (X-position of rack in camera frame(meters))
    rackResponseSuccessStruct.Y = rackCoordinate.Y;                              //4 byte  (Y-position of rack in camera frame(meters))
    rackResponseSuccessStruct.Z = rackCoordinate.Z;                              //4 byte  (Z-position of rack in camera frame(meters))
    rackResponseSuccessStruct.roll = rackCoordinate.roll;                        //4 byte (Rotation of rack about x-axis (radians))
    rackResponseSuccessStruct.pitch = rackCoordinate.pitch;                      //4 byte (Rotation of rack about y-axis (radians))
    rackResponseSuccessStruct.yaw = rackCoordinate.yaw;                          //4 byte (Rotation of rack about z-axis (radians))
    rackResponseSuccessStruct.side = rackCoordinate.side;
    rackResponseSuccessStruct.flag = rackCoordinate.flag;
    strncpy(rackResponseSuccessStruct.stopSequence,seqEnd,6);
}
QByteArray pdsRackResponseClass::ToSuccessArray()
{
    rackResponseSuccessStruct.commandID = swapUInt32(rackResponseSuccessStruct.commandID);
    rackResponseSuccessStruct.errorCode = swapInt32(rackResponseSuccessStruct.errorCode);
    rackResponseSuccessStruct.len = swapUInt32(rackResponseSuccessStruct.len);
    rackResponseSuccessStruct.flag = swapUInt32(rackResponseSuccessStruct.flag);

    QByteArray array;
    array.clear();
    array.append((char*)&rackResponseSuccessStruct,sizeof(rackResponseSuccessStruct));

    for(uint32_t i =0;i<8;i++)      //float transform
    {
        uint32_t index = 16 + 4*i;    //16 + 4*7 = 44
        reverseByte(array,index,index+3);
    }
    return array;
}

pdsRackResponseClass::pdsRackResponseClass(QByteArray array)
{
    int count = array.count();
    if(count == 22)
    {
        getRackResponse_failure* data = (getRackResponse_failure*)array.data();
        data->commandID = swapUInt32(data->commandID);
        data->errorCode = swapInt32(data->errorCode);
        data->len = swapUInt32(data->len);
        strncpy(rackResponseFailureStruct.startSequnce,data->startSequnce,4);
        rackResponseFailureStruct.commandID = data->commandID;
        rackResponseFailureStruct.errorCode = data->errorCode;
        rackResponseFailureStruct.len = data->len;
        strncpy(rackResponseFailureStruct.stopSequence,data->stopSequence,6);
    }

    if(count == 59)
    {
        getRackResponse_success* data = (getRackResponse_success*)array.data();
        data->commandID = swapUInt32(data->commandID);
        data->errorCode = swapInt32(data->errorCode);
        data->len = swapUInt32(data->len);
        strncpy(rackResponseSuccessStruct.startSequnce,data->startSequnce,4);
        rackResponseSuccessStruct.commandID = data->commandID;
        rackResponseSuccessStruct.errorCode = data->errorCode;
        rackResponseSuccessStruct.len = data->len;
        rackResponseSuccessStruct.elapsedTime = byte2Float(array,16);
        rackResponseSuccessStruct.confidence = byte2Float(array,20);
        rackResponseSuccessStruct.X = byte2Float(array,24);
        rackResponseSuccessStruct.Y = byte2Float(array,28);
        rackResponseSuccessStruct.Z = byte2Float(array,32);
        rackResponseSuccessStruct.roll = byte2Float(array,36);
        rackResponseSuccessStruct.pitch = byte2Float(array,40);
        rackResponseSuccessStruct.yaw = byte2Float(array,44);
        rackResponseSuccessStruct.side = data->side;
        rackResponseSuccessStruct.flag = swapUInt32(data->flag);
        strncpy(rackResponseSuccessStruct.stopSequence,data->stopSequence,6);
    }
}
void pdsRackResponseClass::ToString()
{

}
