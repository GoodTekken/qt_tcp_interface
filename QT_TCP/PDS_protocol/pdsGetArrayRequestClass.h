#ifndef PDSGETARRAYREQUESTCLASS_H
#define PDSGETARRAYREQUESTCLASS_H
#include<PDS_protocol/pdsStruct.h>
#include<Function/function.h>
#include<PDS_protocol/arrayid.h>
#include<QObject>
#include<cstring>
class pdsGetArrayRequestClass
{
public:
    pdsGetArrayRequestClass();
    ~pdsGetArrayRequestClass();
    pdsGetArrayRequestClass(arrayID id);
    pdsGetArrayRequestClass(QByteArray array);
    QByteArray toArray();
private:
   getArrayRequest request;
};
//testcase 73 74 61 72 00 00 00 02 00 00 00 04 00 00 00 01 73 74 6f 70 0d 0a
#endif // PDSGETARRAYREQUESTCLASS_H
