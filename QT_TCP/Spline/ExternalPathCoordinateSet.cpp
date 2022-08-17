#include "ExternalPathCoordinateSet.h"


ExternalPathCoordinateSet::ExternalPathCoordinateSet()
{
	;
}
ExternalPathCoordinateSet::~ExternalPathCoordinateSet()
{
	;
}

ExternalPathCoordinateSet::ExternalPathCoordinateSet(CoordinateClass beginPoint, CoordinateClass endPoint)
{

    StartPointX = beginPoint.X;
    StartPointY = beginPoint.Y;
    StartPointAngle = static_cast<int>(beginPoint.Angle*100); //18000 = 180度

    EndPointX = endPoint.X;
    EndPointY = endPoint.Y;
    EndPointAngle = static_cast<int>(endPoint.Angle*100); //18000 = 180度

    CoorXList[1] = StartPointX;
    CoorYList[1] = StartPointY;
    CoorXList[8] = EndPointX;
    CoorYList[8] = EndPointY;

    CoorXList[0] = CoorXList[1] + static_cast<int>(300 * cos(StartPointAngle / 100.0 * (M_PI / 180)));
    CoorYList[0] = CoorYList[1] + static_cast<int>(300 * sin(StartPointAngle / 100.0 * (M_PI / 180)));
    CoorXList[2] = CoorXList[1] - static_cast<int>(300 * cos(StartPointAngle / 100.0 * (M_PI / 180)));
    CoorYList[2] = CoorYList[1] - static_cast<int>(300 * sin(StartPointAngle / 100.0 * (M_PI / 180)));

    CoorXList[7] = CoorXList[8] + static_cast<int>(300 * cos(EndPointAngle / 100.0 * (M_PI / 180)));
    CoorYList[7] = CoorYList[8] + static_cast<int>(300 * sin(EndPointAngle / 100.0 * (M_PI / 180)));
    CoorXList[9] = CoorXList[8] - static_cast<int>(300 * cos(EndPointAngle / 100.0 * (M_PI / 180)));
    CoorYList[9] = CoorYList[8] - static_cast<int>(300 * sin(EndPointAngle / 100.0 * (M_PI / 180)));

    CoorXList[6] = CoorXList[8] + static_cast<int>(600 * cos(EndPointAngle / 100.0 * (M_PI / 180)));//  #700
    CoorYList[6] = CoorYList[8] + static_cast<int>(600 * sin(EndPointAngle / 100.0 * (M_PI / 180)));//  #700
    CoorXList[5] = CoorXList[8] + static_cast<int>(900 * cos(EndPointAngle / 100.0 * (M_PI / 180)));// #1100
    CoorYList[5] = CoorYList[8] + static_cast<int>(900 * sin(EndPointAngle / 100.0 * (M_PI / 180)));// #1100

    CoorXList[3] = (CoorXList[2] * 2 + CoorXList[5]) / 3;
    CoorYList[3] = (CoorYList[2] * 2 + CoorYList[5]) / 3;
    CoorXList[4] = (CoorXList[2] + CoorXList[5] * 2) / 3;
    CoorYList[4] = (CoorYList[2] + CoorYList[5] * 2) / 3;
}


ExternalPathCoordinateSet::ExternalPathCoordinateSet(int StartX, int StartY, int StartAngle, int EndX, int EndY, int EndAngle)
{
    StartPointX = StartX;
    StartPointY = StartY;
    StartPointAngle = StartAngle; //18000 = 180度

    EndPointX = EndX;
    EndPointY = EndY;
    EndPointAngle = EndAngle; //18000 = 180度

    CoorXList[1] = StartX;
    CoorYList[1] = StartY;
    CoorXList[8] = EndX;
    CoorYList[8] = EndY;

    CoorXList[0] = CoorXList[1] + static_cast<int>(300 * cos(StartAngle / 100.0 * (M_PI / 180)));
    CoorYList[0] = CoorYList[1] + static_cast<int>(300 * sin(StartAngle / 100.0 * (M_PI / 180)));
    CoorXList[2] = CoorXList[1] - static_cast<int>(300 * cos(StartAngle / 100.0 * (M_PI / 180)));
    CoorYList[2] = CoorYList[1] - static_cast<int>(300 * sin(StartAngle / 100.0 * (M_PI / 180)));

    CoorXList[7] = CoorXList[8] + static_cast<int>(600 * cos(EndAngle / 100.0 * (M_PI / 180)));//300
    CoorYList[7] = CoorYList[8] + static_cast<int>(600 * sin(EndAngle / 100.0 * (M_PI / 180)));//300
    CoorXList[9] = CoorXList[8] - static_cast<int>(600 * cos(EndAngle / 100.0 * (M_PI / 180)));//300
    CoorYList[9] = CoorYList[8] - static_cast<int>(600 * sin(EndAngle / 100.0 * (M_PI / 180)));//300

    CoorXList[6] = CoorXList[8] + static_cast<int>(800 * cos(EndAngle / 100.0 * (M_PI / 180)));//  #700   600
    CoorYList[6] = CoorYList[8] + static_cast<int>(800 * sin(EndAngle / 100.0 * (M_PI / 180)));//  #700   600
    CoorXList[5] = CoorXList[8] + static_cast<int>(1300 * cos(EndAngle / 100.0 * (M_PI / 180)));// #1100   900
    CoorYList[5] = CoorYList[8] + static_cast<int>(1300 * sin(EndAngle / 100.0 * (M_PI / 180)));// #1100   900

    CoorXList[3] = (CoorXList[2] * 2 + CoorXList[5]) / 3;
    CoorYList[3] = (CoorYList[2] * 2 + CoorYList[5]) / 3;
    CoorXList[4] = (CoorXList[2] + CoorXList[5] * 2) / 3;
    CoorYList[4] = (CoorYList[2] + CoorYList[5] * 2) / 3;
}

vector<byte> ExternalPathCoordinateSet::GetExternalPathByteFromStartToEnd()
{
    data.clear();
    short speed = -300;
    data.push_back(0X64);//报头
    data.push_back(0X00);
    data.push_back(0X5c);//数据长度（92,0x5c）
    data.push_back(0X00);
    data.push_back(0X01);//指令码
    data.push_back(0X00);
    data.push_back(static_cast<byte>(speed & 0xFF));
    data.push_back(static_cast<byte>((speed >> 8) & 0xFF));
    data.push_back(static_cast<byte>(StartPointAngle & 0xFF));
    data.push_back(static_cast<byte>((StartPointAngle >> 8) & 0xFF));
    data.push_back(static_cast<byte>(EndPointAngle & 0xFF));
    data.push_back(static_cast<byte>((EndPointAngle >> 8) & 0xFF));
    for (int i = 0; i < 10; i++)
    {
        data.push_back(static_cast<byte>(CoorXList[i] & 0xFF));
        data.push_back(static_cast<byte>((CoorXList[i] >> 8) & 0xFF));
        data.push_back(static_cast<byte>((CoorXList[i] >> 16) & 0xFF));
        data.push_back(static_cast<byte>((CoorXList[i] >> 24) & 0xFF));
        
        data.push_back(static_cast<byte>(CoorYList[i] & 0xFF));
        data.push_back(static_cast<byte>((CoorYList[i] >> 8) & 0xFF));
        data.push_back(static_cast<byte>((CoorYList[i] >> 16) & 0xFF));
        data.push_back(static_cast<byte>((CoorYList[i] >> 24) & 0xFF));
    }
    return data;
}
vector<byte> ExternalPathCoordinateSet::GetExternalPathByteFromEndToStart()
{
    data.clear();
    short speed = 300;
    data.push_back(0X64);//报头
    data.push_back(0X00);
    data.push_back(0X5c);//数据长度（92,0x5c）
    data.push_back(0X00);
    data.push_back(0X01);//指令码
    data.push_back(0X00);
    data.push_back(static_cast<byte>(speed & 0xFF));
    data.push_back(static_cast<byte>((speed >> 8) & 0xFF));
    data.push_back(static_cast<byte>(EndPointAngle & 0xFF));
    data.push_back(static_cast<byte>((EndPointAngle >> 8) & 0xFF));
    data.push_back(static_cast<byte>(StartPointAngle & 0xFF));
    data.push_back(static_cast<byte>((StartPointAngle >> 8) & 0xFF));
    for (int i = 9; i >= 0; i--)
    {
        data.push_back(static_cast<byte>(CoorXList[i] & 0xFF));
        data.push_back(static_cast<byte>((CoorXList[i] >> 8) & 0xFF));
        data.push_back(static_cast<byte>((CoorXList[i] >> 16) & 0xFF));
        data.push_back(static_cast<byte>((CoorXList[i] >> 24) & 0xFF));
        
        data.push_back(static_cast<byte>(CoorYList[i] & 0xFF));
        data.push_back(static_cast<byte>((CoorYList[i] >> 8) & 0xFF));
        data.push_back(static_cast<byte>((CoorYList[i] >> 16) & 0xFF));
        data.push_back(static_cast<byte>((CoorYList[i] >> 24) & 0xFF));
    }
    return data;
}

QByteArray ExternalPathCoordinateSet::GetExternalPathByteFromStartToEnd_Byte()
{
    bytedata.clear();
    short speed = -300;
    bytedata.append(static_cast<char>(0X64));//报头
    bytedata.append(static_cast<char>(0X00));
    bytedata.append(static_cast<char>(0X5c));//数据长度（92,0x5c）
    bytedata.append(static_cast<char>(0X00));
    bytedata.append(static_cast<char>(0X01));//指令码
    bytedata.append(static_cast<char>(0X00));
    bytedata.append(static_cast<char>(speed & 0xFF));
    bytedata.append(static_cast<char>((speed >> 8) & 0xFF));
    bytedata.append(static_cast<char>(StartPointAngle & 0xFF));
    bytedata.append(static_cast<char>((StartPointAngle >> 8) & 0xFF));
    bytedata.append(static_cast<char>(EndPointAngle & 0xFF));
    bytedata.append(static_cast<char>((EndPointAngle >> 8) & 0xFF));
    for (int i = 0; i < 10; i++)
    {
        bytedata.append(static_cast<char>(CoorXList[i] & 0xFF));
        bytedata.append(static_cast<char>((CoorXList[i] >> 8) & 0xFF));
        bytedata.append(static_cast<char>((CoorXList[i] >> 16) & 0xFF));
        bytedata.append(static_cast<char>((CoorXList[i] >> 24) & 0xFF));

        bytedata.append(static_cast<char>(CoorYList[i] & 0xFF));
        bytedata.append(static_cast<char>((CoorYList[i] >> 8) & 0xFF));
        bytedata.append(static_cast<char>((CoorYList[i] >> 16) & 0xFF));
        bytedata.append(static_cast<char>((CoorYList[i] >> 24) & 0xFF));
    }
    return bytedata;
}
QByteArray ExternalPathCoordinateSet::GetExternalPathByteFromEndToStart_Byte()
{
    bytedata.clear();
    short speed = 300;
    bytedata.append(static_cast<char>(0X64));//报头
    bytedata.append(static_cast<char>(0X00));
    bytedata.append(static_cast<char>(0X5c));//数据长度（92,0x5c）
    bytedata.append(static_cast<char>(0X00));
    bytedata.append(static_cast<char>(0X01));//指令码
    bytedata.append(static_cast<char>(0X00));
    bytedata.append(static_cast<char>(speed & 0xFF));
    bytedata.append(static_cast<char>((speed >> 8) & 0xFF));
    bytedata.append(static_cast<char>(EndPointAngle & 0xFF));
    bytedata.append(static_cast<char>((EndPointAngle >> 8) & 0xFF));
    bytedata.append(static_cast<char>(StartPointAngle & 0xFF));
    bytedata.append(static_cast<char>((StartPointAngle >> 8) & 0xFF));
    for (int i = 9; i >= 0; i--)
    {
        bytedata.append(static_cast<char>(CoorXList[i] & 0xFF));
        bytedata.append(static_cast<char>((CoorXList[i] >> 8) & 0xFF));
        bytedata.append(static_cast<char>((CoorXList[i] >> 16) & 0xFF));
        bytedata.append(static_cast<char>((CoorXList[i] >> 24) & 0xFF));

        bytedata.append(static_cast<char>(CoorYList[i] & 0xFF));
        bytedata.append(static_cast<char>((CoorYList[i] >> 8) & 0xFF));
        bytedata.append(static_cast<char>((CoorYList[i] >> 16) & 0xFF));
        bytedata.append(static_cast<char>((CoorYList[i] >> 24) & 0xFF));
    }
    return bytedata;
}

