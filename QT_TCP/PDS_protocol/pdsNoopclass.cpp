#include "PDS_protocol/pdsNoopclass.h"
#include<cstring>
#include<QObject>
noopClass::noopClass()
{
    std::strncpy(request.startSequnce,seqStart,4);
    request.argsLen=0;
    request.commandID=0;
    std::strncpy(request.stopSequence,seqEnd,6);
}
noopClass::noopClass(uint32_t commandID)
{
    assert(commandID==0);
    std::strncpy(request.startSequnce,seqStart,4);
    request.argsLen=0;
    request.commandID=commandID;
    std::strncpy(request.stopSequence,seqEnd,6);
}
noopClass::noopClass(QByteArray rawBytes){
   std::memcpy(&request,rawBytes.data(),sizeof(noopRequest));
}
QByteArray noopClass::toArray(){
    QByteArray temp;
    temp.resize(sizeof(noopRequest));
    std::memcpy(temp.begin(),&request,sizeof(noopRequest));
    return  temp;
}

noopClass::~noopClass(){

}
