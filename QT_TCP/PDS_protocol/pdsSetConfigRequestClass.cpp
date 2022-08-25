#include "pdsSetConfigRequestClass.h"
#include "Function/function.h"

pdsSetConfigRequestClass::pdsSetConfigRequestClass()
{
    strncpy(setConfigRequestStruct.startSequnce,seqStart,4);
    setConfigRequestStruct.commandID=8;
    setConfigRequestStruct.argsLen=0;
    strncpy(setConfigRequestStruct.stopSequence,seqEnd,6);
    this->arrayLen =0;
}


pdsSetConfigRequestClass::~pdsSetConfigRequestClass()
{
    ;
}

pdsSetConfigRequestClass::pdsSetConfigRequestClass(uint32_t arrayLen,char*rawArrayData)
{
    this->arrayLen=arrayLen;

    strncpy(setConfigRequestStruct.startSequnce,seqStart,4);
    setConfigRequestStruct.commandID=8;
    setConfigRequestStruct.argsLen= arrayLen;
    strncpy(setConfigRequestStruct.stopSequence,seqEnd,6);
    arrayData=new char[arrayLen];

    for (uint32_t i=0;i< arrayLen;i++)
    {
       arrayData[i] = rawArrayData[i];
    }

    setConfigRequestStruct.configs=arrayData;
}

QByteArray pdsSetConfigRequestClass::ToArray()
{
    QByteArray array;
    if(arrayLen==0)
    {
        array.resize(18);
        memcpy(array.begin(),&setConfigRequestStruct,16);
        reverseByte(array,4,7);
        reverseByte(array,8,11);
        strncpy(array.begin()+12,seqEnd,6);
//        array[12] = 0x73;//73 74 6f 70 0d 0a
//        array[13] = 0x74;
//        array[14] = 0x6f;
//        array[15] = 0x70;
//        array[16] = 0x0d;
//        array[17] = 0x0a;
        return  array;
    }
    else
    {
        array.resize(16+arrayLen);
        memcpy(array.begin(),&setConfigRequestStruct,16+arrayLen);
        reverseByte(array,4,7);
        reverseByte(array,8,11);
        memcpy(array.begin()+12,arrayData,arrayLen);
        strncpy(array.begin()+12+arrayLen,seqEnd,6);
//        array[12+arrayLen] = 0x73;//73 74 6f 70 0d 0a
//        array[13+arrayLen] = 0x74;
//        array[14+arrayLen] = 0x6f;
//        array[15+arrayLen] = 0x70;
//        array[26+arrayLen] = 0x0d;
//        array[27+arrayLen] = 0x0a;

        return  array;
    }
}

pdsSetConfigRequestClass::pdsSetConfigRequestClass(QByteArray array)
{
    if(array.length()==18)
    {
        reverseByte(array,4,7);
        reverseByte(array,8,11);
        memcpy(&setConfigRequestStruct,array.data(),12);
        setConfigRequestStruct.stopSequence[0]=array[12];
        setConfigRequestStruct.stopSequence[1]=array[13];
        setConfigRequestStruct.stopSequence[2]=array[14];
        setConfigRequestStruct.stopSequence[3]=array[15];
        setConfigRequestStruct.stopSequence[4]=array[16];
        setConfigRequestStruct.stopSequence[5]=array[17];
        arrayLen=0;
        arrayData=nullptr;
    }
    else
    {
        reverseByte(array,4,7);
        reverseByte(array,8,11);
        memcpy(&setConfigRequestStruct,array.data(),12);
        arrayLen = setConfigRequestStruct.argsLen;
        arrayData=new char[arrayLen];
        for(uint i=0;i<arrayLen;i++)
        {
            arrayData[i]= array[12+i];
        }
//        getConfigResponseStruct.payload=arrayData;

        setConfigRequestStruct.stopSequence[0]=array[16+arrayLen];
        setConfigRequestStruct.stopSequence[1]=array[17+arrayLen];
        setConfigRequestStruct.stopSequence[2]=array[18+arrayLen];
        setConfigRequestStruct.stopSequence[3]=array[19+arrayLen];
        setConfigRequestStruct.stopSequence[4]=array[20+arrayLen];
        setConfigRequestStruct.stopSequence[5]=array[21+arrayLen];
    }
}


//char* arrayData;
//uint32_t arrayLen;
//setConfigRequest setConfigRequestStruct;

