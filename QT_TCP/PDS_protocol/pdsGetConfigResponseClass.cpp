#include "pdsGetConfigResponseClass.h"
#include "Function/function.h"

pdsGetConfigResponseClass::pdsGetConfigResponseClass()
{
    strncpy(getConfigResponseStruct.startSequnce,seqStart,4);
    getConfigResponseStruct.commandID=7;
    getConfigResponseStruct.errorCode=0;
    getConfigResponseStruct.len=6;
    strncpy(getConfigResponseStruct.stopSequence,seqEnd,6);
    this->arrayLen =0;
}

pdsGetConfigResponseClass::pdsGetConfigResponseClass(uint32_t arrayLen,char*rawArrayData)
{
    strncpy(getConfigResponseStruct.startSequnce,seqStart,4);
    getConfigResponseStruct.commandID=7;
    getConfigResponseStruct.errorCode=1;
    getConfigResponseStruct.len=6+arrayLen;
    strncpy(getConfigResponseStruct.stopSequence,seqEnd,6);
    this->arrayLen=arrayLen;
    arrayData=new char[arrayLen];

    for (uint32_t i=0;i< arrayLen;i++)
    {
       arrayData[i] = rawArrayData[i];
    }

    getConfigResponseStruct.payload=arrayData;
}

pdsGetConfigResponseClass::~pdsGetConfigResponseClass()
{
    ;
}

QByteArray pdsGetConfigResponseClass::ToArray()
{
    QByteArray array;
    if(arrayLen==0)
    {
        array.resize(22);
        memcpy(array.begin(),&getConfigResponseStruct,16);
        reverseByte(array,4,7);
        reverseByte(array,8,11);
        reverseByte(array,12,15);
        array[16] = 0x73;//73 74 6f 70 0d 0a
        array[17] = 0x74;
        array[18] = 0x6f;
        array[19] = 0x70;
        array[20] = 0x0d;
        array[21] = 0x0a;
        return  array;
    }
    else {
        array.resize(22+arrayLen);
        memcpy(array.begin(),&getConfigResponseStruct,16+arrayLen);
        reverseByte(array,4,7);
        reverseByte(array,8,11);
        reverseByte(array,12,15);

        memcpy(array.begin()+16,arrayData,arrayLen);

        array[16+arrayLen] = 0x73;//73 74 6f 70 0d 0a
        array[17+arrayLen] = 0x74;
        array[18+arrayLen] = 0x6f;
        array[19+arrayLen] = 0x70;
        array[20+arrayLen] = 0x0d;
        array[21+arrayLen] = 0x0a;

        return  array;
    }
}

pdsGetConfigResponseClass::pdsGetConfigResponseClass(QByteArray array)
{
    if(array.length()==22)
    {
        reverseByte(array,4,7);
        reverseByte(array,8,11);
        reverseByte(array,12,15);
        memcpy(&getConfigResponseStruct,array.data(),16);
        getConfigResponseStruct.stopSequence[0]=array[16];
        getConfigResponseStruct.stopSequence[1]=array[17];
        getConfigResponseStruct.stopSequence[2]=array[18];
        getConfigResponseStruct.stopSequence[3]=array[19];
        getConfigResponseStruct.stopSequence[4]=array[20];
        getConfigResponseStruct.stopSequence[5]=array[21];
        arrayLen=0;
        arrayData=nullptr;
    }
    else
    {
        reverseByte(array,4,7);
        reverseByte(array,8,11);
        reverseByte(array,12,15);
        memcpy(&getConfigResponseStruct,array.data(),16);
        arrayLen = getConfigResponseStruct.len-6;
        arrayData=new char[arrayLen];
        for(int i=0;i<arrayLen;i++)
        {
            arrayData[i]= array[16+i];
        }
//        getConfigResponseStruct.payload=arrayData;

        getConfigResponseStruct.stopSequence[0]=array[16+arrayLen];
        getConfigResponseStruct.stopSequence[1]=array[17+arrayLen];
        getConfigResponseStruct.stopSequence[2]=array[18+arrayLen];
        getConfigResponseStruct.stopSequence[3]=array[19+arrayLen];
        getConfigResponseStruct.stopSequence[4]=array[20+arrayLen];
        getConfigResponseStruct.stopSequence[5]=array[21+arrayLen];
    }
}
