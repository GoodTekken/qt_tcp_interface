#ifndef PDSSETCONFIGRESPONSECLASS_H
#define PDSSETCONFIGRESPONSECLASS_H
#include <QObject>
#include "PDS_protocol/pdsStruct.h"

class pdsSetConfigResponseClass
{
public:

    setConfigResponse setConfigResponseStruct;

    pdsSetConfigResponseClass();
    ~pdsSetConfigResponseClass();
    QByteArray ToArray();
    pdsSetConfigResponseClass(QByteArray array);
};

#endif // PDSSETCONFIGRESPONSECLASS_H
