#ifndef PDSRACKREQUESTCLASS_H
#define PDSRACKREQUESTCLASS_H
#include <QObject>
#include "PDS_protocol/pdsStruct.h"

class pdsRackRequestClass
{
public:
    getRackRequest rackRequestStruct;

    pdsRackRequestClass();     //default: command Id - 4
    ~pdsRackRequestClass();
    pdsRackRequestClass(uint32_t commandID, float depthHint);
    pdsRackRequestClass(QByteArray array);  //for receive template
    QByteArray ToArray();
    void ToString();
};

#endif // PDSRACKREQUESTCLASS_H
