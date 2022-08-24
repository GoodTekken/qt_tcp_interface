#include "pdsSaveExtrinsicsResponseClass.h"

pdsSaveExtrinsicsResponseClass::pdsSaveExtrinsicsResponseClass()
{
    std::strncpy(response.startSequnce,seqStart,4);
    std::strncpy(response.stopSequence,seqEnd,6);
    response.len=6;
    response.errorCode=0;
    response.commandID=11;
}
pdsSaveExtrinsicsResponseClass::~pdsSaveExtrinsicsResponseClass()
{

}
pdsSaveExtrinsicsResponseClass::pdsSaveExtrinsicsResponseClass(QByteArray array)
{
    reverseByte(array,4,7);
    reverseByte(array,8,11);
    reverseByte(array,12,15);
    std::memcpy(&response,array.data(),sizeof (saveExtrinsicsResponse));
}
pdsSaveExtrinsicsResponseClass::pdsSaveExtrinsicsResponseClass(int32_t errorCode)
{
    std::strncpy(response.startSequnce,seqStart,4);
    std::strncpy(response.stopSequence,seqEnd,6);
    response.len=6;
    response.errorCode=errorCode;
    response.commandID=11;
}

QByteArray pdsSaveExtrinsicsResponseClass::toArray()
{
    QByteArray array{sizeof (saveExtrinsicsResponse),0};
    std::memcpy(array.begin(),&response,sizeof (saveExtrinsicsResponse));
    reverseByte(array,4,7);
    reverseByte(array,8,11);
    reverseByte(array,12,15);
    return  array;
}
