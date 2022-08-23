#ifndef PDSPALLETCOORDINATECLASS_H
#define PDSPALLETCOORDINATECLASS_H
#include "PDS_protocol/pdsStruct.h"

class pdsPalletCoordinateClass
{
public:
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

    pdsPalletCoordinateClass();
    ~pdsPalletCoordinateClass();
    pdsPalletCoordinateClass(float elapsedTime,
                             float confidence,
                             pds_point centerPoint,
                             pds_point leftPoint,
                             pds_point rightPoint,
                             pds_posture posture);
    void ToString();
};

#endif // PDSPALLETCOORDINATECLASS_H
