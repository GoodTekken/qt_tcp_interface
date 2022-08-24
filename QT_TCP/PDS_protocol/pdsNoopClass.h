#ifndef NOOPCLASS_H
#define NOOPCLASS_H
#include "PDS_protocol/pdsStruct.h"
#include<QObject>
class pdsNoopRequest
{
public:
    pdsNoopRequest();
    ~pdsNoopRequest();
    pdsNoopRequest(QByteArray rawBytes);
    pdsNoopRequest(uint32_t commandID);
    QByteArray toArray();
    //void TOstring();
private:
    noopRequest request;
};
class pdsNoopResponse
{
public:
    pdsNoopResponse();
    ~pdsNoopResponse();
    pdsNoopResponse(uint32_t commandID,int32_t err_code);
    pdsNoopResponse(QByteArray rawBytes);
    QByteArray toArray();
private:
    noopResponse response;
};
//testcase 73 74 61 72 00 00 00 00 00 00 00 00 73 74 6f 70 0d 0a
//return 73 74 61 72 00 00 00 00 00 00 00 00 00 00 00 06 73 74 6f 70 0d 0a
#endif // NOOPCLASS_H
