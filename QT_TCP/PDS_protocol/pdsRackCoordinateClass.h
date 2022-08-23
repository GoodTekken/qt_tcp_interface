#ifndef PDSRACKCOORDINATECLASS_H
#define PDSRACKCOORDINATECLASS_H
#include "PDS_protocol/pdsStruct.h"


class pdsRackCoordinateClass
{
public:
    float elapsedTime;              //4 byte  (time use to detect)
    float confidence;               //4 byte (Currently Unused)
    float   X;                      //4 byte (rack x position in camera frame)
    float   Y;                      //4 byte (rack y position in camera frame)
    float   Z;                      //4 byte (rack z position in camera frame)
    float   roll;                   //4 byte (Rotation of rack about x-axis (radians))
    float   pitch;                  //4 byte (Rotation of rack about y-axis (radians))
    float   yaw;                    //4 byte (Rotation of rack about z-axis (radians))
    uint8_t side;                   //1 byte (0 left 1 middle(usually not happen) 2 right)
    uint32_t flag;                  //4 byte (detail are belows)

    pdsRackCoordinateClass();
    ~pdsRackCoordinateClass();
    pdsRackCoordinateClass(float elapsedTime,
                             float confidence,
                             pds_point rack_position,
                             pds_posture rack_posture,
                           uint8_t side,
                           uint32_t flag);
    void ToString();
};

#endif // PDSRACKCOORDINATECLASS_H
