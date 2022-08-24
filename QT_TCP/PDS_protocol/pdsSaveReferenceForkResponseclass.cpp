#include "PDS_protocol/pdsSaveReferenceForkResponseclass.h"

pdsSaveReferenceForkResponseClass::pdsSaveReferenceForkResponseClass()
{
    std::strncpy(response.startSequnce,seqStart,4);
    response.len=6;
    response.commandID=3;
    response.errorCode=0;
    std::strncpy(response.stopSequence,seqEnd,6);
}
pdsSaveReferenceForkResponseClass::pdsSaveReferenceForkResponseClass(uint32_t commandID,int32_t errorCode)
{
    assert(commandID==3);
    std::strncpy(response.startSequnce,seqStart,4);
    response.len=6;
    response.commandID=3;
    response.errorCode=errorCode;
    std::strncpy(response.stopSequence,seqEnd,6);
}
pdsSaveReferenceForkResponseClass::pdsSaveReferenceForkResponseClass(QByteArray array)
{
    reverseByte(array,4,7);
    reverseByte(array,12,16);
    std::memcpy(&response,array.data(),sizeof (saveReferenceForkResponse));
}
QByteArray pdsSaveReferenceForkResponseClass::toArray()
{
    QByteArray array;
    array.resize(sizeof (saveReferenceForkResponse));
    std::memcpy(array.begin(),&response,sizeof (saveReferenceForkResponse));
    reverseByte(array,4,7);
    reverseByte(array,12,16);
    return  array;
}
pdsSaveReferenceForkResponseClass::~pdsSaveReferenceForkResponseClass()
{

}
