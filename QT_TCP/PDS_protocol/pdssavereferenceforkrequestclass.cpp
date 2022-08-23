#ifndef aaa
#define aaa
#include "PDS_protocol/pdssavereferenceforkrequestclass.h"
#include<cstring>
#include<Function/function.h>
#include<algorithm>
pdsSaveReferenceForkRequestClass::pdsSaveReferenceForkRequestClass()
{
    std::strncpy(request.startSequnce,seqStart,4);
    request.commandID=3;
    request.argsLen=0;
    std::strncpy(request.stopSequence,seqEnd,4);
}
pdsSaveReferenceForkRequestClass::pdsSaveReferenceForkRequestClass(uint32_t commandID){
    assert(commandID==3);
    std::strncpy(request.startSequnce,seqStart,4);
    request.commandID=commandID;
    request.argsLen=0;
    std::strncpy(request.stopSequence,seqEnd,4);
}
pdsSaveReferenceForkRequestClass::pdsSaveReferenceForkRequestClass(QByteArray rawByteArray){
    //rawByteArray must be a structed saveReferenceRequest
    assert(rawByteArray.length()==18);
    reverseByte(rawByteArray,4,7);
    std::memcpy(&request,rawByteArray.data(),sizeof(saveReferenceForkRequest));
    swapUInt32(request.commandID);
}
pdsSaveReferenceForkRequestClass::~pdsSaveReferenceForkRequestClass(){

}
QByteArray pdsSaveReferenceForkRequestClass::toArray(){
    QByteArray temp;
    temp.resize(sizeof (saveReferenceForkRequest));
    std::memcpy(temp.begin(),&request,sizeof(saveReferenceForkRequest));
    //deal with the turned problem
    reverseByte(temp,4,7);
    return  temp;
}
#endif
