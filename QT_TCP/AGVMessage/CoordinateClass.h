#ifndef COORDINATECASS_H
#define COORDINATECASS_H

#include <cstdint>
#include <string>

class CoordinateClass
{
public:
    int X;
    int Y;
    int Z;
    double Angle;
    bool UpSideDown;  //用于相机是否倒立安装

    CoordinateClass();
    ~CoordinateClass();
    CoordinateClass(int x, int y, int z, double angle);
    CoordinateClass(int x, int y, int z, double angle, bool upsidedown);


    void ToString();
};

#endif // COORDINATECASS_H
