#pragma once
#include <math.h> 
#include <vector>
#include <QByteArray>
#include <AGVMessage/CoordinateClass.h>
#define M_PI 3.14159265358979323846
typedef unsigned char byte;
using namespace std;

class ExternalPathCoordinateSet
{
public:
	int CoorXList[10];
	int CoorYList[10];

	int StartPointX;
	int StartPointY;
	int StartPointAngle; //18000 = 180度

	int EndPointX;
	int EndPointY;
	int EndPointAngle; //18000 = 180度

    vector<byte> data;
    QByteArray bytedata;

	ExternalPathCoordinateSet();
	~ExternalPathCoordinateSet();
    ExternalPathCoordinateSet(CoordinateClass beginPoint, CoordinateClass endPoint);
	ExternalPathCoordinateSet(int StartX, int StartY, int StartAngle, int EndX, int EndY, int EndAngle);

    vector<byte> GetExternalPathByteFromStartToEnd();
    vector<byte> GetExternalPathByteFromEndToStart();

    QByteArray GetExternalPathByteFromStartToEnd_Byte();
    QByteArray GetExternalPathByteFromEndToStart_Byte();

};

/*测试数据
(后退:92个字节)->Agv_Coordinate(0, 0, 18000, 1500, 300, 18000);
原始：64 00 5C 00 01 00 D4 FE 50 46 50 46 D4 FE FF FF 00 00 00 00 00 00 00 00 00 00 00 00 2C 01 00 00 00 00 00 00 90 01 00 00 64 00 00 00 F4 01 00 00 C8 00 00 00 58 02 00 00 2C 01 00 00 84 03 00 00 2C 01 00 00 B0 04 00 00 2C 01 00 00 DC 05 00 00 2C 01 00 00 08 07 00 00 2C 01 00 00
现在：64 00 5C 00 01 00 D4 FE 50 46 50 46 D4 FE FF FF 00 00 00 00 00 00 00 00 00 00 00 00 2C 01 00 00 00 00 00 00 90 01 00 00 64 00 00 00 F4 01 00 00 C8 00 00 00 58 02 00 00 2C 01 00 00 84 03 00 00 2C 01 00 00 B0 04 00 00 2C 01 00 00 DC 05 00 00 2C 01 00 00 08 07 00 00 2C 01 00 00

(前进:92个字节)->Agv_Coordinate(0, 0, 18000, 1500, 300, 18000);
原始：64 00 5C 00 01 00 2C 01 50 46 50 46 08 07 00 00 2C 01 00 00 DC 05 00 00 2C 01 00 00 B0 04 00 00 2C 01 00 00 84 03 00 00 2C 01 00 00 58 02 00 00 2C 01 00 00 F4 01 00 00 C8 00 00 00 90 01 00 00 64 00 00 00 2C 01 00 00 00 00 00 00 00 00 00 00 00 00 00 00 D4 FE FF FF 00 00 00 00
现在：64 00 5C 00 01 00 2C 01 50 46 50 46 08 07 00 00 2C 01 00 00 DC 05 00 00 2C 01 00 00 B0 04 00 00 2C 01 00 00 84 03 00 00 2C 01 00 00 58 02 00 00 2C 01 00 00 F4 01 00 00 C8 00 00 00 90 01 00 00 64 00 00 00 2C 01 00 00 00 00 00 00 00 00 00 00 00 00 00 00 D4 FE FF FF 00 00 00 00
*/
