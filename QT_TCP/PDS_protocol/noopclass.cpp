#include "PDS_protocol/noopclass.h"
#include<cstring>
noopClass::noopClass()
{
    std::strncpy(request.startSequnce,seqStart,4);
    request.argsLen=0;
    request.commandID=0;
    std::strncpy(request.stopSequence,seqEnd,4);
}
noopClass::noopClass(uint32_t commandID)
{
    assert(commandID==0);
    std::strncpy(request.startSequnce,seqStart,4);
    request.argsLen=0;
    request.commandID=commandID;
    std::strncpy(request.stopSequence,seqEnd,4);
}
noopClass::noopClass(QByteArray rawBytes){
   std::memcpy(&request,rawBytes.data(),sizeof(noopRequest));
}
QByteArray noopClass::toArray(){
    char rq_data[sizeof(noopRequest)];
    std::memcpy(&rq_data,&request,sizeof (noopRequest));
    QByteArray temp(rq_data);
    return  temp;
}

