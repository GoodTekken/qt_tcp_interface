#ifndef AGVEXTERNALPARA_H
#define AGVEXTERNALPARA_H


#include "CommunicationClass.h"
#include "AGVMessage/CoordinateClass.h"
#include "RequestExternalClass.h"

#include <QObject>
#include <QMutex>
#include <QSharedPointer>

//以AgvID为索引，对应的获取全部的内容
class AGVExternalPara : public QObject
{
     Q_OBJECT
public:
    static QSharedPointer<AGVExternalPara> getIntance();

    int AgvID;
    void SetID(int id);

    //AGV通信端口
    CommunicationClass VehicleCommunication;
    //相机通信端口
    CommunicationClass CameraCommunication;
    //外部路径申请
    RequestExternalClass RequestExternal;
    //Agv Reference Point AGV实际所在坐标
    CoordinateClass AgvReferencePointPosition;
    //CameraPosition 相机的安装位置
    CoordinateClass CameraPosition;
    //RackPosition   相机检测出来的货架位置
    CoordinateClass RackPosition;
    //LayoutPosition 从地图wef文件中获取线段的坐标，用于样条曲线入站的起点。(反之，出站时的终点)
    CoordinateClass LayoutStartPosition;
    //坐标矩阵整合后的最终坐标，用于样条曲线入站的终点。(反之，出站时的起点)
    CoordinateClass LayoutEndPosition;
    //主要作用是在AGV确认货架前面的坐标以后，AGV继续往里面行走的距离。
    CoordinateClass RackParameter;
    void ToString();


private:
    explicit AGVExternalPara(QObject *parent = 0);
    AGVExternalPara& operator = (AGVExternalPara&)=delete;
    AGVExternalPara(AGVExternalPara&) = delete;


private:
    static QSharedPointer<AGVExternalPara> m_AGVExternalPara_ptr;
    static QMutex m_mutex;

};


extern QSharedPointer<AGVExternalPara> g_AGV_ptr;

#endif // AGVEXTERNALPARA_H
