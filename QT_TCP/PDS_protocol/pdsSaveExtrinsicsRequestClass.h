#ifndef PDSSAVEEXTRINSICSREQUESTCLASS_H
#define PDSSAVEEXTRINSICSREQUESTCLASS_H
#include<cstring>
#include"Function/function.h"
#include"PDS_protocol/pdsStruct.h"
class pdsSaveExtrinsicsRequestClass
{
public:
    pdsSaveExtrinsicsRequestClass();
    ~pdsSaveExtrinsicsRequestClass();
    pdsSaveExtrinsicsRequestClass(pds_point position,pds_posture posture);
    pdsSaveExtrinsicsRequestClass(QByteArray array);
    QByteArray toArray();
private:
    saveExtrinsicsRequest request;
};
//test case 73 74 61 72 00 00 00 0b 00 00 00 18 3f 8c cc cd 40 0c cc cd 40 53 33 33 3f 00 00 00 3f 19 99 9a 3f 33 33 33 73 74 6f 70 0d 0a
#endif // PDSSAVEEXTRINSICSREQUESTCLASS_H
