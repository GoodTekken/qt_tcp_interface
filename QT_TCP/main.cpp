#include <QApplication>
#include <ros/ros.h>
#include <pcl_ros/point_cloud.h>
#include <pcl_conversions/pcl_conversions.h>

#include "main.h"
#include "serverwidget.h"
#include "clientwidget.h"
#include "Math/UserMatrix.h"

QSharedPointer<AGVExternalPara> g_AGV_ptr = AGVExternalPara::getIntance();

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ServerWidget server_weight;
    server_weight.show();

    ClientWidget client_weight;
    client_weight.show();

    return a.exec();
}
