#include "pdsResetConfigRequestClass.h"

pdsResetConfigRequestClass::pdsResetConfigRequestClass()
{
    std::strncpy(request.startSequnce,seqStart,4);
    request.argsLen=0;
    request.commandID=10;
    std::strncpy(request.stopSequence,seqEnd,6);
}

pdsResetConfigRequestClass::~pdsResetConfigRequestClass()
{

}
pdsResetConfigRequestClass::pdsResetConfigRequestClass(QByteArray array)
{
    //
    reverseByte(array,4,7);
    reverseByte(array,8,11);
    std::memcpy(&request,array.data(),sizeof (saveConfigRequest));
}
QByteArray pdsResetConfigRequestClass::toArray()
{
    QByteArray array;
    array.resize(sizeof (saveConfigRequest));
    std::memcpy(array.begin(),&request,sizeof (saveConfigRequest));
    reverseByte(array,4,7);
    reverseByte(array,8,11);
    return  array;
}
