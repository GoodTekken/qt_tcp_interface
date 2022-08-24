#ifndef PDSRESETCONFIGREQUESTCLASS_H
#define PDSRESETCONFIGREQUESTCLASS_H
#include<Function/function.h>
#include<PDS_protocol/pdsStruct.h>
#include<cstring>
class pdsResetConfigRequestClass
{
public:
    pdsResetConfigRequestClass();
    ~pdsResetConfigRequestClass();
    pdsResetConfigRequestClass(QByteArray array);
    QByteArray toArray();
private:
   resetConfigRequest request;
};

//test case 73 74 61 72 00 00 00 0a 00 00 00 00 73 74 6f 70 0d 0a
#endif // PDSRESETCONFIGREQUESTCLASS_H
