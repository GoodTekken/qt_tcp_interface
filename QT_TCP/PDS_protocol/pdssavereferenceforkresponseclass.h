#ifndef PDSSAVEREFERENCEFORKRESPONSECLASS_H
#define PDSSAVEREFERENCEFORKRESPONSECLASS_H
#include<QObject>
#include"PDS_protocol/pdsStruct.h"
#include"Function/function.h"
#include<cstring>
class pdsSaveReferenceForkResponseClass
{
public:
    pdsSaveReferenceForkResponseClass();
    ~pdsSaveReferenceForkResponseClass();
    pdsSaveReferenceForkResponseClass(uint32_t commandID,int32_t errorCode=0);
    pdsSaveReferenceForkResponseClass(QByteArray array);
    QByteArray toArray();
private:
    saveReferenceForkResponse response;
};

#endif // PDSSAVEREFERENCEFORKRESPONSECLASS_H
