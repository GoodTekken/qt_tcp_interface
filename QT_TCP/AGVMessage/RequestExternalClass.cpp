#include "RequestExternalClass.h"

RequestExternalClass::RequestExternalClass()
{
    RequestExternalSegmentSignal = false;
    RequestExternalSegmentID = 0;
}

RequestExternalClass::~RequestExternalClass()
{
    ;
}

RequestExternalClass::RequestExternalClass(bool reqExternalSegmentSignal, int reqExternalSegmentID)
{
    RequestExternalSegmentSignal = reqExternalSegmentSignal;
    RequestExternalSegmentID = reqExternalSegmentID;
}


void RequestExternalClass::ToString()
{
    printf("requestExternalSegmentSignal:{ %d } requestExternalSegmentID:{ %d }", RequestExternalSegmentSignal, RequestExternalSegmentID);
}
