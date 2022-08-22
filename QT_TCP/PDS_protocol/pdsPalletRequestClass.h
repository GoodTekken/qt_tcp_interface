#ifndef PDSPALLETREQUESTCLASS_H
#define PDSPALLETREQUESTCLASS_H

#include <cstdint>
#include <string>
#include <QObject>

#include"PDS_protocol/pdsStruct.h"

class pdsPalletRequestClass
{
public:

    getPalletRequest palletRequestStruct;
    float depthHint;          //just for float-byte transform test

    pdsPalletRequestClass();     //default: command Id - 1,pallet type - 1
    ~pdsPalletRequestClass();
    pdsPalletRequestClass(uint32_t commandID, uint16_t palletType);
    pdsPalletRequestClass(QByteArray array);  //for receive template
    QByteArray ToArray();
    void ToString();
};
#endif // PDSPALLETREQUESTCLASS_H
