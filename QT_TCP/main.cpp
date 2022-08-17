#include "serverwidget.h"
#include <QApplication>
#include "clientwidget.h"

#include <ros/ros.h>
#include <pcl_ros/point_cloud.h>
#include <pcl_conversions/pcl_conversions.h>

#include "main.h"
#include "Math/UserMatrix.h"

QSharedPointer<AGVExternalPara> g_AGV_ptr = AGVExternalPara::getIntance();
//extern QSharedPointer<AGVExternalPara> g_AGV_ptr;
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ServerWidget w;
    w.show();

    ClientWidget w2;
    w2.show();

    abc_test = 2;
    g_AGV_ptr->AgvID =1;
    g_AGV_ptr->SetID(1);
    g_AGV_ptr->LayoutStartPosition = CoordinateClass(53907,22995,0,90);       //1,Map start point coordinate
//  g_AGV_ptr->AgvReferencePointPosition = CoordinateClass(11000,11000,0,0);  //2,
    g_AGV_ptr->CameraPosition = CoordinateClass(700,30,0,1.5);                  //3,
//  g_AGV_ptr->RackPosition = CoordinateClass(-2000,0,0,45);                  //4,


//    Matrix<double, 4, 4> temp1 = MatrixObject(g_AGV_ptr->AgvReferencePointPosition)*MatrixObject(g_AGV_ptr->CameraPosition);
//    Matrix<double, 4, 4> temp2 = temp1*MatrixObject(g_AGV_ptr->RackPosition);
//    posture pallectCoordinate = GetPosture(temp2);

//    g_AGV_ptr->LayoutEndPosition = CoordinateClass(pallectCoordinate.x,
//                                              pallectCoordinate.y,
//                                              pallectCoordinate.z,
//                                              pallectCoordinate.angle);

//    g_AGV_ptr->ToString();

    return a.exec();
}
