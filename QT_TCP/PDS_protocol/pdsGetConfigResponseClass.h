#ifndef PDSGETCONFIGRESPONSECLASS_H
#define PDSGETCONFIGRESPONSECLASS_H

#include <QObject>
#include "PDS_protocol/pdsStruct.h"

class pdsGetConfigResponseClass
{
public:

    getConfigResponse getConfigResponseStruct;

    pdsGetConfigResponseClass();
    ~pdsGetConfigResponseClass();
    pdsGetConfigResponseClass(uint32_t arrayLen,char*rawArrayData);

    QByteArray ToArray();
    pdsGetConfigResponseClass(QByteArray array);

    char* arrayData;
    uint32_t arrayLen;
};

#endif // PDSGETCONFIGRESPONSECLASS_H
