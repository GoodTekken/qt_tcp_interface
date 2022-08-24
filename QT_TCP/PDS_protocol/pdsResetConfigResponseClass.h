#ifndef PDSRESETCONFIGRESPONSECLASS_H
#define PDSRESETCONFIGRESPONSECLASS_H
#include<cstring>
#include"Function/function.h"
#include"PDS_protocol/pdsStruct.h"

class pdsResetConfigResponseClass
{
public:
    pdsResetConfigResponseClass();
    ~pdsResetConfigResponseClass();
    pdsResetConfigResponseClass(int32_t errorCode);
    pdsResetConfigResponseClass(QByteArray array);
    QByteArray toArray();
private:
    resetConfigResponse response;
};

#endif // PDSRESETCONFIGRESPONSECLASS_H
