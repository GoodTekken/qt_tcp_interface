#ifndef PDSSAVECONFIGREQUESTCLASS_H
#define PDSSAVECONFIGREQUESTCLASS_H
#include<Function/function.h>
#include<PDS_protocol/pdsStruct.h>
#include<cstring>
class pdsSaveConfigRequestClass
{
public:
    pdsSaveConfigRequestClass();
    ~pdsSaveConfigRequestClass();
    pdsSaveConfigRequestClass(QByteArray array);
    QByteArray toArray();
private:
   saveConfigRequest request;
};
//test case 73 74 61 72 00 00 00 09 00 00 00 00 73 74 6f 70 0d 0a
#endif // PDSSAVECONFIGREQUESTCLASS_H
