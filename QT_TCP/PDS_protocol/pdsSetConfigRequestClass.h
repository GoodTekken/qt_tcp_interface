#ifndef PDSSETCONFIGREQUESTCLASS_H
#define PDSSETCONFIGREQUESTCLASS_H
#include <QObject>
#include "PDS_protocol/pdsStruct.h"

class pdsSetConfigRequestClass
{
public:
    char* arrayData;
    uint32_t arrayLen;
    setConfigRequest setConfigRequestStruct;

    pdsSetConfigRequestClass();
    ~pdsSetConfigRequestClass();
    pdsSetConfigRequestClass(uint32_t arrayLen,char*rawArrayData);
    QByteArray ToArray();
    pdsSetConfigRequestClass(QByteArray array);
};

#endif // PDSSETCONFIGREQUESTCLASS_H
