#include "CoordinateClass.h"

CoordinateClass::CoordinateClass()
{
    X = 0;
    Y = 0;
    Z = 0;
    Angle = 0;
    UpSideDown = false;
}

CoordinateClass::~CoordinateClass()
{
    ;//析构函数
}
CoordinateClass::CoordinateClass(int x, int y, int z, double angle)
{
    X = x;
    Y = y;
    Z = z;
    Angle = angle;
    UpSideDown = false;
}

CoordinateClass::CoordinateClass(int x, int y, int z, double angle, bool upsidedown)
{
    X = x;
    Y = y;
    Z = z;
    Angle = angle;
    UpSideDown = upsidedown;
}

void CoordinateClass::ToString()
{
    printf("X: %d  Y: %d  Z: %d  Angle: %f  UpSideDown: %d", X, Y, Z, Angle, UpSideDown);
}
