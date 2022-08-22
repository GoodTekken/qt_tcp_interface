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

void pdsPalletResponseClass::response_success(pdsPalletCoordinateClass palletCoordinate)
{
    palletResponseSuccessStruct.startSequnce[0] = 0x73;//73 74 61 72
    palletResponseSuccessStruct.startSequnce[1] = 0x74;
    palletResponseSuccessStruct.startSequnce[2] = 0x61;
    palletResponseSuccessStruct.startSequnce[3] = 0x72;

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

    palletResponseSuccessStruct.stopSequence[0] = 0x73;//73 74 6f 70 0d 0a
    palletResponseSuccessStruct.stopSequence[1] = 0x74;
    palletResponseSuccessStruct.stopSequence[2] = 0x6f;
    palletResponseSuccessStruct.stopSequence[3] = 0x70;
    palletResponseSuccessStruct.stopSequence[4] = 0x0d;
    palletResponseSuccessStruct.stopSequence[5] = 0x0a;
    ;
}
QByteArray pdsPalletResponseClass::ToSuccessArray()
{
    palletResponseSuccessStruct.commandID = swapUInt32(palletResponseSuccessStruct.commandID);
    palletResponseSuccessStruct.errorCode = swapInt32(palletResponseSuccessStruct.errorCode);
    palletResponseSuccessStruct.len = swapUInt32(palletResponseSuccessStruct.len);

    QByteArray array;
    array.clear();
    unsigned char buf[78];
    std::memcpy(buf,(char*)&palletResponseSuccessStruct,sizeof(palletResponseSuccessStruct));
    for(int i= 0;i<16;i++)
    {
        array.append(buf[i]);
    }

    for(int i =0;i<14;i++)
    {
        int index = 16 + 4*i;    //16 + 4*13 = 68
        array.append(buf[index+3]);
        array.append(buf[index+2]);
        array.append(buf[index+1]);
        array.append(buf[index]);
    }

    for(int i= 72;i<78;i++)
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

    if(count == 78)
    {
        getPalletResponse_success* data = (getPalletResponse_success*)array.data();
        data->commandID = swapUInt32(data->commandID);
        data->errorCode = swapInt32(data->errorCode);
        data->len = swapUInt32(data->len);
        palletResponseSuccessStruct.startSequnce[0] = data->startSequnce[0];
        palletResponseSuccessStruct.startSequnce[1] = data->startSequnce[1];
        palletResponseSuccessStruct.startSequnce[2] = data->startSequnce[2];
        palletResponseSuccessStruct.startSequnce[3] = data->startSequnce[3];
        palletResponseSuccessStruct.commandID = data->commandID;
        palletResponseSuccessStruct.errorCode = data->errorCode;
        palletResponseSuccessStruct.len = data->len;
        QByteArray array_temp;
        array_temp.append(array[16]);
        array_temp.append(array[17]);
        array_temp.append(array[18]);
        array_temp.append(array[19]);
        palletResponseSuccessStruct.elapsedTime = Byte2Float(array_temp);
        array_temp.clear();
        array_temp.append(array[20]);
        array_temp.append(array[21]);
        array_temp.append(array[22]);
        array_temp.append(array[23]);
        palletResponseSuccessStruct.confidence = Byte2Float(array_temp);
        array_temp.clear();
        array_temp.append(array[24]);
        array_temp.append(array[25]);
        array_temp.append(array[26]);
        array_temp.append(array[27]);
        palletResponseSuccessStruct.palletX = Byte2Float(array_temp);
        array_temp.clear();
        array_temp.append(array[28]);
        array_temp.append(array[29]);
        array_temp.append(array[30]);
        array_temp.append(array[31]);
        palletResponseSuccessStruct.palletY = Byte2Float(array_temp);
        array_temp.clear();
        array_temp.append(array[32]);
        array_temp.append(array[33]);
        array_temp.append(array[34]);
        array_temp.append(array[35]);
        palletResponseSuccessStruct.palletZ = Byte2Float(array_temp);
        array_temp.clear();
        array_temp.append(array[36]);
        array_temp.append(array[37]);
        array_temp.append(array[38]);
        array_temp.append(array[39]);
        palletResponseSuccessStruct.leftPocketX = Byte2Float(array_temp);
        array_temp.clear();
        array_temp.append(array[40]);
        array_temp.append(array[41]);
        array_temp.append(array[42]);
        array_temp.append(array[43]);
        palletResponseSuccessStruct.leftPocketY = Byte2Float(array_temp);
        array_temp.clear();
        array_temp.append(array[44]);
        array_temp.append(array[45]);
        array_temp.append(array[46]);
        array_temp.append(array[47]);
        palletResponseSuccessStruct.leftPocketZ = Byte2Float(array_temp);
        array_temp.clear();
        array_temp.append(array[48]);
        array_temp.append(array[49]);
        array_temp.append(array[50]);
        array_temp.append(array[51]);
        palletResponseSuccessStruct.rightPocketX = Byte2Float(array_temp);
        array_temp.clear();
        array_temp.append(array[52]);
        array_temp.append(array[53]);
        array_temp.append(array[54]);
        array_temp.append(array[55]);
        palletResponseSuccessStruct.rightPocketY = Byte2Float(array_temp);
        array_temp.clear();
        array_temp.append(array[56]);
        array_temp.append(array[57]);
        array_temp.append(array[58]);
        array_temp.append(array[59]);
        palletResponseSuccessStruct.rightPocketZ = Byte2Float(array_temp);
        array_temp.clear();
        array_temp.append(array[60]);
        array_temp.append(array[61]);
        array_temp.append(array[62]);
        array_temp.append(array[63]);
        palletResponseSuccessStruct.roll = Byte2Float(array_temp);
        array_temp.clear();
        array_temp.append(array[64]);
        array_temp.append(array[65]);
        array_temp.append(array[66]);
        array_temp.append(array[67]);
        palletResponseSuccessStruct.pitch = Byte2Float(array_temp);
        array_temp.clear();
        array_temp.append(array[68]);
        array_temp.append(array[69]);
        array_temp.append(array[70]);
        array_temp.append(array[71]);
        palletResponseSuccessStruct.yaw = Byte2Float(array_temp);

        palletResponseSuccessStruct.stopSequence[0] = data->stopSequence[0];
        palletResponseSuccessStruct.stopSequence[1] = data->stopSequence[1];
        palletResponseSuccessStruct.stopSequence[2] = data->stopSequence[2];
        palletResponseSuccessStruct.stopSequence[3] = data->stopSequence[3];
        palletResponseSuccessStruct.stopSequence[4] = data->stopSequence[4];
        palletResponseSuccessStruct.stopSequence[5] = data->stopSequence[5];
    }
}

void pdsPalletResponseClass::ToString()
{
    printf("HelloWorld:{ %d } requestExternalSegmentID:{ %d }",
           0,
           0);
};
