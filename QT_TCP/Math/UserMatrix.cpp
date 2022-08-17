#include "UserMatrix.h"


Matrix<double, 4, 4> MatrixObject(int x, int y, int z, double angle)   //x,y,z坐标,角度
{
    double theta = angle * M_PI / 180.0;
    Matrix<double, 4, 4>  mytrix_44;
    mytrix_44 << cos(theta), -sin(theta), 0, x,
        sin(theta), cos(theta), 0, y,
        0, 0, 1, z,
        0, 0, 0, 1;
    return mytrix_44;
}


Matrix<double, 4, 4> MatrixObject(CoordinateClass temp_coordinate)
{
    int x = temp_coordinate.X;
    int y = temp_coordinate.Y;
    int z = temp_coordinate.Z;
    double angle = temp_coordinate.Angle;
    bool upsidedown = temp_coordinate.UpSideDown;

    if (upsidedown == false)
    {
        return MatrixObject(x, y, z, angle);
    }
    else
    {
        return MatrixObject(x, -y, -z, -angle);
    }
}


/// <summary>
/// 获取物体的位姿信息
/// </summary>
/// <returns></returns>
posture GetPosture(Matrix<double,4,4> mymatrix)
{
    posture post = posture();
    post.x = static_cast<int>(mymatrix(0, 3));
    post.y = static_cast<int>(mymatrix(1, 3));
    post.z = static_cast<int>(mymatrix(2, 3));
    if (mymatrix(1, 0) < 0)
    {
        post.angle = -acos(mymatrix(0, 0)) * 180.0 / M_PI;
    }
    else
    {
        post.angle = acos(mymatrix(0, 0)) * 180.0 / M_PI;
    }

    return post;
}


QPoint GetMiddlePoint(QPoint startpoint,QPoint endpoint)
{
    int tempX = static_cast<int>((startpoint.x() + endpoint.x()) / 2);
    int tempY = static_cast<int>((startpoint.y() + endpoint.y()) / 2);
    QPoint middlePoint = QPoint(tempX, tempY);
    return middlePoint;
}

line_struct TwoPointToLine(QPoint startPoint, QPoint endPoint)
{
    //斜率k=(y1-y2)/(x1-x2)
    double RCB = static_cast<double>(endPoint.y() - startPoint.y() ) / (endPoint.x() -startPoint.x());
    //回归系数a   y = bx + a => a = y - bx
    double RCA = startPoint.y() - RCB * startPoint.x();
    double angle = 180 * atan(RCB) / M_PI;

    line_struct param;
    param.RCB = RCB;
    param.RCA = RCA;
    param.angle = angle;
    return param;
}
