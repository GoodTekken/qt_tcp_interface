#ifndef PDSVOLCHECKRESPONSECLASS_H
#define PDSVOLCHECKRESPONSECLASS_H
#include <QObject>
#include "PDS_protocol/pdsStruct.h"

class pdsVolCheckResponseClass
{
public:

    volCheckResponse volCheckResponseStruct;

    pdsVolCheckResponseClass();
    ~pdsVolCheckResponseClass();
    pdsVolCheckResponseClass(int errorCode,int Npix);    //Number of pixels in the VOI
    QByteArray ToArray();
    pdsVolCheckResponseClass(QByteArray array);
};

#endif // PDSVOLCHECKRESPONSECLASS_H
