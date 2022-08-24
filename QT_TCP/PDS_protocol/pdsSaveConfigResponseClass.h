#ifndef PDSSAVECONFIGRESPONSECLASS_H
#define PDSSAVECONFIGRESPONSECLASS_H
#include<cstring>
#include"Function/function.h"
#include"PDS_protocol/pdsStruct.h"

class pdsSaveConfigResponseClass
{
public:
    pdsSaveConfigResponseClass();
    ~pdsSaveConfigResponseClass();
    pdsSaveConfigResponseClass(int32_t errorCode);
    pdsSaveConfigResponseClass(QByteArray array);
    QByteArray toArray();
private:
    saveConfigResponse response;
};

#endif // PDSSAVECONFIGRESPONSECLASS_H
