#ifndef PDSVOLCHECKREQUESTCLASS_H
#define PDSVOLCHECKREQUESTCLASS_H

#include <QObject>
#include "PDS_protocol/pdsStruct.h"

class pdsVolCheckRequestClass
{
public:
    volCheckRequest volCheckRequestStruct;

    pdsVolCheckRequestClass();
    ~pdsVolCheckRequestClass();
    pdsVolCheckRequestClass(pds_point min,pds_point max);
    QByteArray ToArray();
    pdsVolCheckRequestClass(QByteArray array);

};

#endif // PDSVOLCHECKREQUESTCLASS_H
