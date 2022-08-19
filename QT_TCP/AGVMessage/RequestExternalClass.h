#ifndef REQUESTEXTERNALCLASS_H
#define REQUESTEXTERNALCLASS_H

#include <string>
#include "Function/function.h"

class RequestExternalClass
{
public:
    bool RequestExternalSegmentSignal;
    int RequestExternalSegmentID;

    RequestExternalClass();
    ~RequestExternalClass();
    RequestExternalClass(bool reqExternalSegmentSignal, int reqExternalSegmentID);

    void ToString();
};

#endif // REQUESTEXTERNALCLASS_H
