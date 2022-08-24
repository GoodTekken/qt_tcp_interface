#ifndef PDSSAVEEXTRINSICSRESPONSECLASS_H
#define PDSSAVEEXTRINSICSRESPONSECLASS_H
#include<cstring>
#include"Function/function.h"
#include"PDS_protocol/pdsStruct.h"

class pdsSaveExtrinsicsResponseClass
{
public:
    pdsSaveExtrinsicsResponseClass();
    ~pdsSaveExtrinsicsResponseClass();
    pdsSaveExtrinsicsResponseClass(int32_t errorCode);
    pdsSaveExtrinsicsResponseClass(QByteArray array);
    QByteArray toArray();
private:
    saveExtrinsicsResponse response;
};

#endif // PDSSAVEEXTRINSICSRESPONSECLASS_H
