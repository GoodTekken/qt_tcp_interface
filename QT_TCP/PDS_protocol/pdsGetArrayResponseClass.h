#ifndef PDSGETARRAYRESPONSECLASS_H
#define PDSGETARRAYRESPONSECLASS_H
#include"Function/function.h"
#include"PDS_protocol/arrayid.h"
#include"PDS_protocol/pdsStruct.h"
#include"cstring"
class pdsGetArrayResponseClass
{
public:
    pdsGetArrayResponseClass();
    ~pdsGetArrayResponseClass();
    pdsGetArrayResponseClass(uint32_t arrayLen,char*rawArrayData,arrayType*typeInfo=nullptr);
    pdsGetArrayResponseClass(QByteArray array);
    QByteArray toArray();
private:
    char*arrayData;
    uint32_t arrayLen;
    union{
        getArrayResponse_success success_response;
        getArrayResponse_failure failure_response;
    };
};

#endif // PDSGETARRAYRESPONSECLASS_H
