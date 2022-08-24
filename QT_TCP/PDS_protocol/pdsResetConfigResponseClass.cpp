#include "pdsResetConfigResponseClass.h"
pdsResetConfigResponseClass::pdsResetConfigResponseClass()
{
    std::strncpy(response.startSequnce,seqStart,4);
    std::strncpy(response.stopSequence,seqEnd,6);
    response.len=6;
    response.errorCode=0;
    response.commandID=10;
}
pdsResetConfigResponseClass::~pdsResetConfigResponseClass()
{

}
pdsResetConfigResponseClass::pdsResetConfigResponseClass(QByteArray array)
{
    reverseByte(array,4,7);
    reverseByte(array,8,11);
    reverseByte(array,12,15);
    std::memcpy(&response,array.data(),sizeof (resetConfigResponse));
}
pdsResetConfigResponseClass::pdsResetConfigResponseClass(int32_t errorCode)
{
    std::strncpy(response.startSequnce,seqStart,4);
    std::strncpy(response.stopSequence,seqEnd,6);
    response.len=6;
    response.errorCode=errorCode;
    response.commandID=10;
}

QByteArray pdsResetConfigResponseClass::toArray()
{
    QByteArray array{sizeof (resetConfigResponse),0};
    std::memcpy(array.begin(),&response,sizeof (resetConfigResponse));
    reverseByte(array,4,7);
    reverseByte(array,8,11);
    reverseByte(array,12,15);
    return  array;
}
