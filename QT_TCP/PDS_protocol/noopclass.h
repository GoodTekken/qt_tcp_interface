#ifndef NOOPCLASS_H
#define NOOPCLASS_H
#include "PDS_protocol/pdsStruct.h"
#include<QObject>
class noopClass
{
public:
    noopClass();
    ~noopClass();
    noopClass(QByteArray rawBytes);
    noopClass(uint32_t commandID);
    QByteArray toArray();
    //void TOstring();
private:
    noopRequest request;
};
//testcase 73 74 61 72 00 00 00 00 00 00 00 00 73 74 6f 70 0d 0a
//return 73 74 61 72 00 00 00 00 00 00 00 00 00 00 00 06 73 74 6f 70 0d 0a
#endif // NOOPCLASS_H
