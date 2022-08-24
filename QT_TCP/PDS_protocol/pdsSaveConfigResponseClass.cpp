#include "pdsSaveConfigResponseClass.h"

pdsSaveConfigResponseClass::pdsSaveConfigResponseClass()
{
    std::strncpy(response.startSequnce,seqStart,4);
    std::strncpy(response.stopSequence,seqEnd,6);
    response.len=6;
    response.errorCode=0;
    response.commandID=9;
}
pdsSaveConfigResponseClass::~pdsSaveConfigResponseClass()
{

}
pdsSaveConfigResponseClass::pdsSaveConfigResponseClass(QByteArray array)
{
    reverseByte(array,4,7);
    reverseByte(array,8,11);
    reverseByte(array,12,15);
    std::memcpy(&response,array.data(),sizeof (saveConfigResponse));
}
pdsSaveConfigResponseClass::pdsSaveConfigResponseClass(int32_t errorCode)
{
    std::strncpy(response.startSequnce,seqStart,4);
    std::strncpy(response.stopSequence,seqEnd,6);
    response.len=6;
    response.errorCode=errorCode;
    response.commandID=9;
}

QByteArray pdsSaveConfigResponseClass::toArray()
{
    QByteArray array{sizeof (saveConfigResponse),0};
    std::memcpy(array.begin(),&response,sizeof (saveConfigResponse));
    reverseByte(array,4,7);
    reverseByte(array,8,11);
    reverseByte(array,12,15);
    return  array;
}
