#include "pdsGetArrayRequestClass.h"

pdsGetArrayRequestClass::pdsGetArrayRequestClass()
{
    std::strncpy(request.startSequence,seqStart,4);
    std::strncpy(request.stopSequence,seqEnd,6);
    request.argsLen=4;
    request.commandID=2;
    request.arrayID=0;
}
pdsGetArrayRequestClass::pdsGetArrayRequestClass(arrayID id)
{
    std::strncpy(request.startSequence,seqStart,4);
    std::strncpy(request.stopSequence,seqEnd,6);
    request.argsLen=4;
    request.commandID=2;
    request.arrayID=id;
}

pdsGetArrayRequestClass::~pdsGetArrayRequestClass()
{

}
pdsGetArrayRequestClass::pdsGetArrayRequestClass(QByteArray array)
{
    reverseByte(array,4,7);
    reverseByte(array,8,11);
    reverseByte(array,12,15);
    std::memcpy(&request,array.data(),sizeof (getArrayRequest));
}

QByteArray pdsGetArrayRequestClass::toArray()
{
    QByteArray array;
    array.resize(sizeof(getArrayRequest));
    std::memcpy(array.begin(),&request,sizeof (getArrayRequest));
    reverseByte(array,4,7);
    reverseByte(array,8,11);
    reverseByte(array,12,15);
    return  array;
}
