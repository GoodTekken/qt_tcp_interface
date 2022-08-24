#ifndef PDSSAVEREFERENCEFORKREQUESTCLASS_H
#define PDSSAVEREFERENCEFORKREQUESTCLASS_H
#include<QObject>
#include<stdint.h>
#include"PDS_protocol/pdsStruct.h"
class pdsSaveReferenceForkRequestClass
{
public:
    pdsSaveReferenceForkRequestClass();
    pdsSaveReferenceForkRequestClass(uint32_t commandID);
    QByteArray toArray();
    pdsSaveReferenceForkRequestClass(QByteArray rawByteArray);
    ~pdsSaveReferenceForkRequestClass();
private:
    saveReferenceForkRequest request;
};
//test data
//73 74 61 72 00 00 00 03 00 00 00 00 73 74 6f 70 0d 0a
#endif // PDSSAVEREFERENCEFORKREQUESTCLASS_H
