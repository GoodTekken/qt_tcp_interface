#include "pdsSaveExtrinsicsRequestClass.h"

pdsSaveExtrinsicsRequestClass::pdsSaveExtrinsicsRequestClass()
{
    std::strncpy(request.startSequnce,seqStart,4);
    std::strncpy(request.stopSequence,seqEnd,6);
    request.x=1.1;
    request.y=2.2;
    request.z=3.3;
    request.roll=0.5;
    request.pitch=0.6;
    request.yaw=0.7;
    request.argsLen=24;
    request.commandID=11;
}
pdsSaveExtrinsicsRequestClass::~pdsSaveExtrinsicsRequestClass()
{

}
pdsSaveExtrinsicsRequestClass::pdsSaveExtrinsicsRequestClass(pds_point position,pds_posture posture)
{
    std::strncpy(request.startSequnce,seqStart,4);
    std::strncpy(request.stopSequence,seqEnd,6);
    request.argsLen=24;
    request.commandID=11;
    request.x=position.x;
    request.y=position.y;
    request.z=position.z;
    request.roll=posture.roll;
    request.pitch=posture.pitch;
    request.yaw=posture.yaw;
}
pdsSaveExtrinsicsRequestClass::pdsSaveExtrinsicsRequestClass(QByteArray array)
{
    reverseByte(array,4,7);
    reverseByte(array,8,11);
    reverseByte(array,12,15);
    reverseByte(array,16,19);
    reverseByte(array,20,23);
    reverseByte(array,24,27);
    reverseByte(array,28,31);
    reverseByte(array,32,35);
    std::memcpy(&request,array.data(),sizeof (saveExtrinsicsRequest));
}
QByteArray pdsSaveExtrinsicsRequestClass::toArray()
{
    QByteArray array{sizeof (saveExtrinsicsRequest),0};
    std::memcpy(array.begin(),&request,sizeof (saveExtrinsicsRequest));
    reverseByte(array,4,7);
    reverseByte(array,8,11);
    reverseByte(array,12,15);
    reverseByte(array,16,19);
    reverseByte(array,20,23);
    reverseByte(array,24,27);
    reverseByte(array,28,31);
    reverseByte(array,32,35);
    return  array;
}
