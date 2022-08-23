#include "pdsRackCoordinateClass.h"

pdsRackCoordinateClass::pdsRackCoordinateClass()
{

}

pdsRackCoordinateClass::~pdsRackCoordinateClass()
{

}

pdsRackCoordinateClass::pdsRackCoordinateClass(float elapsedTime,
                                                float confidence,
                                                pds_point rack_position,
                                                pds_posture rack_posture,
                                                uint8_t side,
                                                uint32_t flag)
{
    this->elapsedTime = elapsedTime;
    this->confidence = confidence;
    this->X = rack_position.x;
    this->Y = rack_position.y;
    this->Z = rack_position.z;
    this->roll = rack_posture.roll;
    this->pitch = rack_posture.pitch;
    this->yaw = rack_posture.yaw;
    this->side = side;
    this->flag=flag;
}
