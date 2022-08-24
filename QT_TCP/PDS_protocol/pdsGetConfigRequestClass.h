#ifndef PDSGETCONFIGREQUESTCLASS_H
#define PDSGETCONFIGREQUESTCLASS_H
#include <QObject>
#include "PDS_protocol/pdsStruct.h"

class pdsGetConfigRequestClass
{
public:
    getConfigRequest getConfigRequestStruct;

    pdsGetConfigRequestClass();
    ~pdsGetConfigRequestClass();
    QByteArray ToArray();
    pdsGetConfigRequestClass(QByteArray array);
};

#endif // PDSGETCONFIGREQUESTCLASS_H
