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
    strncpy(palletResponseFailureStruct.startSequnce,seqStart,4);
    palletResponseFailureStruct.commandID = commandID;
    palletResponseFailureStruct.errorCode = errorCode;
    palletResponseFailureStruct.len = 6;
    strncpy(palletResponseFailureStruct.stopSequence,seqEnd,6);
}

QByteArray pdsPalletResponseClass::ToFailureArray()
{
    palletResponseFailureStruct.commandID = swapUInt32(palletResponseFailureStruct.commandID);
    palletResponseFailureStruct.errorCode = swapInt32(palletResponseFailureStruct.errorCode);
    palletResponseFailureStruct.len = swapUInt32(palletResponseFailureStruct.len);

    QByteArray array;
    array.clear();
    array.append((char*)&palletResponseFailureStruct,sizeof(palletResponseFailureStruct));
    return array;
}

void pdsPalletResponseClass::response_success(pdsPalletCoordinateClass palletCoordinate)
{
    strncpy(palletResponseSuccessStruct.startSequnce,seqStart,4);
    palletResponseSuccessStruct.commandID = 1;
    palletResponseSuccessStruct.errorCode = 0;
    palletResponseSuccessStruct.len = 62;
    palletResponseSuccessStruct.elapsedTime = palletCoordinate.elapsedTime;          //4 byte  (Elapsed time (sec) of the detection)
    palletResponseSuccessStruct.confidence = palletCoordinate.confidence;            //4 byte  (Average correlation score of the segmented pallet pockets against the pocket-type kernel.)
    palletResponseSuccessStruct.palletX = palletCoordinate.palletX;                  //4 byte  (X-position of pallet in camera frame(meters))
    palletResponseSuccessStruct.palletY = palletCoordinate.palletY;                  //4 byte  (Y-position of pallet in camera frame(meters))
    palletResponseSuccessStruct.palletZ = palletCoordinate.palletZ;                  //4 byte  (Z-position of pallet in camera frame(meters))
    palletResponseSuccessStruct.leftPocketX = palletCoordinate.leftPocketX;          //4 byte  (X-position of left pocket in camera frame(meters))
    palletResponseSuccessStruct.leftPocketY = palletCoordinate.leftPocketY;          //4 byte  (Y-position of left pocket in camera frame(meters))
    palletResponseSuccessStruct.leftPocketZ = palletCoordinate.leftPocketZ;          //4 byte  (Z-position of left pocket in camera frame(meters))
    palletResponseSuccessStruct.rightPocketX = palletCoordinate.rightPocketX;        //4 byte  (X-position of right pocket in camera frame(meters))
    palletResponseSuccessStruct.rightPocketY = palletCoordinate.rightPocketY;        //4 byte  (Y-position of right pocket in camera frame(meters))
    palletResponseSuccessStruct.rightPocketZ = palletCoordinate.rightPocketZ;        //4 byte  (Z-position of right pocket in camera frame(meters))
    palletResponseSuccessStruct.roll = palletCoordinate.roll;                        //4 byte  (Rotation of pallet about the x-axis in the camera frame (radians))
    palletResponseSuccessStruct.pitch = palletCoordinate.pitch;                      //4 byte  (Rotation of pallet about the y-axis in the camera frame (radians))
    palletResponseSuccessStruct.yaw = palletCoordinate.yaw;                          //4 byte  (Rotation of pallet about the z-axis in camera frame (radians))
    strncpy(palletResponseSuccessStruct.stopSequence,seqEnd,6);
}
QByteArray pdsPalletResponseClass::ToSuccessArray()
{
    palletResponseSuccessStruct.commandID = swapUInt32(palletResponseSuccessStruct.commandID);
    palletResponseSuccessStruct.errorCode = swapInt32(palletResponseSuccessStruct.errorCode);
    palletResponseSuccessStruct.len = swapUInt32(palletResponseSuccessStruct.len);

//    unsigned char buf[78];
//    std::memcpy(buf,(char*)&palletResponseSuccessStruct,sizeof(palletResponseSuccessStruct));
    QByteArray array;
    array.clear();
    array.append((char*)&palletResponseSuccessStruct,sizeof(palletResponseSuccessStruct));
    for(uint32_t i =0;i<14;i++)      //float transform
    {
        uint32_t index = 16 + 4*i;    //16 + 4*13 = 68
        reverseByte(array,index,index+3);
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
        strncpy(palletResponseFailureStruct.startSequnce,data->startSequnce,4);
        palletResponseFailureStruct.commandID = data->commandID;
        palletResponseFailureStruct.errorCode = data->errorCode;
        palletResponseFailureStruct.len = data->len;
        strncpy(palletResponseFailureStruct.stopSequence,data->stopSequence,6);
    }

    if(count == 78)
    {
        getPalletResponse_success* data = (getPalletResponse_success*)array.data();
        data->commandID = swapUInt32(data->commandID);
        data->errorCode = swapInt32(data->errorCode);
        data->len = swapUInt32(data->len);
        strncpy(palletResponseSuccessStruct.startSequnce,data->startSequnce,4);
        palletResponseSuccessStruct.commandID = data->commandID;
        palletResponseSuccessStruct.errorCode = data->errorCode;
        palletResponseSuccessStruct.len = data->len;
        palletResponseSuccessStruct.elapsedTime = byte2Float(array,16);
        palletResponseSuccessStruct.confidence = byte2Float(array,20);
        palletResponseSuccessStruct.palletX = byte2Float(array,24);
        palletResponseSuccessStruct.palletY = byte2Float(array,28);
        palletResponseSuccessStruct.palletZ = byte2Float(array,32);
        palletResponseSuccessStruct.leftPocketX = byte2Float(array,36);
        palletResponseSuccessStruct.leftPocketY = byte2Float(array,40);
        palletResponseSuccessStruct.leftPocketZ = byte2Float(array,44);
        palletResponseSuccessStruct.rightPocketX = byte2Float(array,48);
        palletResponseSuccessStruct.rightPocketY = byte2Float(array,52);
        palletResponseSuccessStruct.rightPocketZ = byte2Float(array,56);
        palletResponseSuccessStruct.roll = byte2Float(array,60);
        palletResponseSuccessStruct.pitch = byte2Float(array,64);
        palletResponseSuccessStruct.yaw = byte2Float(array,68);
        strncpy(palletResponseSuccessStruct.stopSequence,data->stopSequence,6);
    }
}

void pdsPalletResponseClass::ToString()
{
    printf("HelloWorld:{ %d } requestExternalSegmentID:{ %d }",
           0,
           0);
};
