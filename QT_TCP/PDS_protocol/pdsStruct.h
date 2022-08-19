#ifndef PDSSTRUCT_H
#define PDSSTRUCT_H
#include <cstdint>

#pragma pack(1)     //设置结构体为1字节对齐
typedef struct
{
                                   //total: 25 bytes
    char     startSequnce[4];      //4 byte  (The fixed byte string: (115, 116, 97, 114) aka (‘s’, ‘t’, ‘a’, ‘r’))
    uint32_t commandID;            //4 byte  (value: 1,The command id of the request being sent)
    uint32_t argsLen;              //4 byte  (value: 7,The size in bytes of the arguments sent to the command)
    uint16_t palletType;           //2 byte  (value: 1 = CHEP_FRONT, 2=CHEP_SIDE,3=GMA, 4=BLOCK, 5=STRINGER,6=COMPOSED_BLOCK*)
    float    depthHint;            //4 byte  (Depth hint from front of camera glass in meters)
    uint8_t  filterMask;           //1 byte  (bit0 = stray light filter, bit1 = fast flying pixel filter, bit2 = stretch wrap filter)
    char     stopSequence[6];      //6 byte  (The fixed byte string: (115, 116, 111, 112, 13, 10) aka (‘s’, ‘t’, ‘o’, ‘p’, ‘\r’, ‘\n’))
}getPalletRequest;
#pragma pack()		//结束结构体对齐设置

typedef struct
{
                                   //total: 78 bytes
    char     startSequnce[4];      //4 byte  (The fixed byte string: (115, 116, 97, 114) aka (‘s’, ‘t’, ‘a’, ‘r’))
    uint32_t commandID;            //4 byte  (value: 1,The command id of the request being sent)
    uint32_t errorCode;            //4 byte  (Unless the return code is PDS_NO_ERRORS, the caller should not attempt the pick)
    uint32_t len;                  //4 byte  (value: 62:56+6,length in bytes of “payload” + “stop sequence)
    float    elapsedTime;          //4 byte  (Elapsed time (sec) of the detection)
    float    confidence;           //4 byte  (Average correlation score of the segmented pallet pockets against the pocket-type kernel.)
    float    palletX;              //4 byte  (X-position of pallet in camera frame(meters))
    float    palletY;              //4 byte  (Y-position of pallet in camera frame(meters))
    float    palletZ;              //4 byte  (Z-position of pallet in camera frame(meters))
    float    leftPocketX;          //4 byte  (X-position of left pocket in camera frame(meters))
    float    leftPocketY;          //4 byte  (Y-position of left pocket in camera frame(meters))
    float    leftPocketZ;          //4 byte  (Z-position of left pocket in camera frame(meters))
    float    rightPocketX;         //4 byte  (X-position of right pocket in camera frame(meters))
    float    rightPocketY;         //4 byte  (Y-position of right pocket in camera frame(meters))
    float    rightPocketZ;         //4 byte  (Z-position of right pocket in camera frame(meters))
    float    roll;                 //4 byte  (Rotation of pallet about the x-axis in the camera frame (radians))
    float    pitch;                //4 byte  (Rotation of pallet about the y-axis in the camera frame (radians))
    float    yaw;                  //4 byte  (Rotation of pallet about the z-axis in camera frame (radians))
    char     stopSequence[6];      //6 byte  (The fixed byte string: (115, 116, 111, 112, 13, 10) aka (‘s’, ‘t’, ‘o’, ‘p’, ‘\r’, ‘\n’))
}getPalletResponse_success;

typedef struct
{
                                   //total: 22 bytes
    char     startSequnce[4];      //4 byte  (The fixed byte string: (115, 116, 97, 114) aka (‘s’, ‘t’, ‘a’, ‘r’))
    uint32_t commandID;            //4 byte  (value: 1,The command id of the request being sent)
    uint32_t errorCode;            //4 byte  (value: Unless the return code is PDS_NO_ERRORS, the caller should not attempt the pick)
    uint32_t len;                  //4 byte  (value: 6,length in bytes of “payload” + “stop sequence)
    char     stopSequence[6];      //6 byte  (The fixed byte string: (115, 116, 111, 112, 13, 10) aka (‘s’, ‘t’, ‘o’, ‘p’, ‘\r’, ‘\n’))
}getPalletResponse_failure;


#endif // PDSSTRUCT_H
