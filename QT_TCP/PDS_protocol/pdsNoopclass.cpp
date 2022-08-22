#include "PDS_protocol/pdsNoopclass.h"
#include<cstring>
#include<QObject>
pdsNoopRequest::pdsNoopRequest()
{
    strncpy(request.startSequnce,seqStart,4);
    request.argsLen=0;
    request.commandID=0;
    strncpy(request.stopSequence,seqEnd,6);
}
pdsNoopRequest::pdsNoopRequest(uint32_t commandID)
{
    assert(commandID==0);
    strncpy(request.startSequnce,seqStart,4);
    request.argsLen=0;
    request.commandID=commandID;
    strncpy(request.stopSequence,seqEnd,6);
}
pdsNoopRequest::pdsNoopRequest(QByteArray rawBytes){
   memcpy(&request,rawBytes.data(),sizeof(noopRequest));
}
QByteArray pdsNoopRequest::toArray(){
    QByteArray temp;
    temp.resize(sizeof(noopRequest));
    memcpy(temp.begin(),&request,sizeof(noopRequest));
    return  temp;
}

pdsNoopRequest::~pdsNoopRequest(){

}
pdsNoopResponse::~pdsNoopResponse(){

}
pdsNoopResponse::pdsNoopResponse(){
    strncpy(response.startSequnce,seqStart,4);
    response.commandID=0;
    response.errorCode=0;
    response.len=6;
    strncpy(response.stopSequence,seqEnd,6);
}
pdsNoopResponse::pdsNoopResponse(uint32_t commandID,int32_t errcode){
    assert(commandID==0);
    strncpy(response.startSequnce,seqStart,4);
    response.commandID=0;
    response.errorCode=errcode;
    response.len=6;
    strncpy(response.stopSequence,seqEnd,6);
}
pdsNoopResponse::pdsNoopResponse(QByteArray array){
    memcpy(&response,array.data(),sizeof(noopResponse));

}

QByteArray pdsNoopResponse::toArray(){
    QByteArray temp;
    temp.resize(sizeof(noopResponse));
    memcpy(temp.begin(),&response,sizeof(noopResponse));
    temp[12]=0x0;
    temp[16]=0x6;
    return  temp;
}

