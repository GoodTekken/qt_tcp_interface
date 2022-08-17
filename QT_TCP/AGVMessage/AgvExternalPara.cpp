#include "AGVMessage/AgvExternalPara.h"


AGVExternalPara::AGVExternalPara(QObject *parent):QObject(parent){}

QSharedPointer<AGVExternalPara> AGVExternalPara::m_AGVExternalPara_ptr;
QMutex AGVExternalPara::m_mutex;

QSharedPointer<AGVExternalPara> AGVExternalPara::getIntance()
{
    if(nullptr == m_AGVExternalPara_ptr)
    {
        m_mutex.lock();
        if(nullptr == m_AGVExternalPara_ptr)
        {
            m_AGVExternalPara_ptr = QSharedPointer<AGVExternalPara>(new AGVExternalPara);
        }
        m_mutex.unlock();
    }

    return m_AGVExternalPara_ptr;
}

void AGVExternalPara::SetID(int id )
{
    AgvID = id;
}

void AGVExternalPara::ToString()
{
    printf("AGVID: %d\r\n", AgvID);
    printf("\r\n VehicleCommunication:\r\n");
    VehicleCommunication.ToString();
    printf("\r\n CameraCommunication:\r\n");
    CameraCommunication.ToString();
    printf("\r\n RequestExternal:\r\n");
    RequestExternal.ToString();
    printf("\r\n AgvReferencePointPosition:\r\n");
    AgvReferencePointPosition.ToString();
    printf("\r\n CameraPosition:\r\n");
    CameraPosition.ToString();
    printf("\r\n RackPosition:\r\n");
    RackPosition.ToString();
    printf("\r\n LayoutEndPosition:\r\n");
    LayoutEndPosition.ToString();
    printf("\r\n RackParameter:\r\n");
    RackParameter.ToString();
}
