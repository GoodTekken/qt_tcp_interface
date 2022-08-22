#include "pdsPalletCoordinateClass.h"

pdsPalletCoordinateClass::pdsPalletCoordinateClass()
{

}

pdsPalletCoordinateClass::~pdsPalletCoordinateClass()
{

}

pdsPalletCoordinateClass::pdsPalletCoordinateClass(float elapsedTime,
                         float confidence,
                         pds_point centerPoint,
                         pds_point leftPoint,
                         pds_point rightPoint,
                         pds_posture posture)
{
    this->elapsedTime = elapsedTime;
    this->confidence = confidence;
    this->palletX = centerPoint.x;
    this->palletY = centerPoint.y;
    this->palletZ = centerPoint.z;
    this->leftPocketX = leftPoint.x;
    this->leftPocketY = leftPoint.y;
    this->leftPocketZ = leftPoint.z;
    this->rightPocketX = rightPoint.x;
    this->rightPocketY = rightPoint.y;
    this->rightPocketZ = rightPoint.z;
    this->roll = posture.roll;
    this->pitch = posture.pitch;
    this->yaw = posture.yaw;
}
