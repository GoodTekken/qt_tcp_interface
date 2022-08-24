#ifndef PDSRACKRESPONSECLASS_H
#define PDSRACKRESPONSECLASS_H
#include <QObject>
#include "PDS_protocol/pdsStruct.h"
#include"PDS_protocol/pdsRackCoordinateClass.h"

class pdsRackResponseClass
{
public:
    getRackResponse_success rackResponseSuccessStruct;
    getRackResponse_failure rackResponseFailureStruct;

    pdsRackResponseClass();
    ~pdsRackResponseClass();

    void response_failure(uint32_t commandID,int32_t errorCode);
    QByteArray ToFailureArray();

    void response_success(pdsRackCoordinateClass rackCoordinate);
    QByteArray ToSuccessArray();

    pdsRackResponseClass(QByteArray array);
    void ToString();
};

#endif // PDSRACKRESPONSECLASS_H
