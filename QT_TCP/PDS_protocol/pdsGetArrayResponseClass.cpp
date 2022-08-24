#include "pdsGetArrayResponseClass.h"

pdsGetArrayResponseClass::pdsGetArrayResponseClass()
{
    failure_response.len=6;
    std::strncpy(failure_response.startSequnce,seqStart,4);
    std::strncpy(failure_response.stopSequence,seqEnd,6);
    failure_response.commandID=2;
    failure_response.errorCode=1;//meaning testing
    arrayData=nullptr;

    arrayLen=0;
}
pdsGetArrayResponseClass::~pdsGetArrayResponseClass()
{
    if(arrayLen==0)
    {
        return;//failure
    }
    else
    {
        delete[] arrayData;
    }
}
pdsGetArrayResponseClass::pdsGetArrayResponseClass(uint32_t arrayLen,char*rawArrayData,arrayType *info)
{
    if(arrayLen==0){
        failure_response.len=6;
        std::strncpy(failure_response.startSequnce,seqStart,4);
        std::strncpy(failure_response.stopSequence,seqEnd,6);
        failure_response.commandID=2;
        failure_response.errorCode=1;//meaning testing
        arrayData=nullptr;
        arrayLen=0;
    }
    else {
        assert(info!=nullptr);
        success_response.len=6+arrayLen+16;
        success_response.commandID=2;
        std::strncpy(success_response.startSequnce,seqStart,4);
        std::strncpy(success_response.stopSequence,seqEnd,6);
        success_response.rows=info->row;
        success_response.columns=info->column;
        success_response.pixelType=info->Pixeltype;
        success_response.errorCode=0;
        success_response.channels=info->channels;
        this->arrayLen=arrayLen;
        arrayData=new char[arrayLen];
        for (uint32_t i=0;i<success_response.rows;i++) {
               std::memcpy(i*success_response.columns+arrayData,rawArrayData+i*success_response.columns,success_response.columns);
        }
        success_response.pixel=arrayData;
    }
}
QByteArray pdsGetArrayResponseClass::toArray()
{
    QByteArray array;
    if(arrayLen==0)
    {
        array.resize(22);
        std::memcpy(array.begin(),&failure_response,22);
        reverseByte(array,4,7);
        reverseByte(array,8,11);
        reverseByte(array,12,15);
        return  array;
    }
    else {
        array.resize(38+arrayLen);
        std::memset(array.begin(),0,38+arrayLen);
        std::memcpy(array.begin(),&success_response,32);
        std::strncpy(array.begin()+32,arrayData,arrayLen);
        std::memcpy(array.begin()+32+arrayLen,seqEnd,6);
        reverseByte(array,4,7);
        reverseByte(array,8,11);
        reverseByte(array,12,15);
        reverseByte(array,16,19);
        reverseByte(array,20,23);
        reverseByte(array,24,27);
        reverseByte(array,28,31);
        return  array;
    }
}
pdsGetArrayResponseClass::pdsGetArrayResponseClass(QByteArray array){
    if(array.length()==22){
        std::memcpy(&failure_response,array.data(),22);
        reverseByte(array,4,7);
        reverseByte(array,8,11);
        reverseByte(array,12,15);
        arrayLen=0;
        arrayData=nullptr;
    }
    else
    {
        reverseByte(array,4,7);
        reverseByte(array,8,11);
        reverseByte(array,12,15);
        reverseByte(array,16,19);
        reverseByte(array,20,23);
        reverseByte(array,24,27);
        reverseByte(array,28,31);
        std::memcpy(&success_response,array.data(),32);
        arrayLen=success_response.len-6-16;
        arrayData=new char[arrayLen];
        std::memcpy(arrayData,array.data()+32,arrayLen);
        success_response.pixel=arrayData;
        std::strncpy(success_response.stopSequence,seqEnd,6);
    }
}
