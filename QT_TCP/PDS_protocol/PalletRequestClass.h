#ifndef PALLETREQUESTCLASS_H
#define PALLETREQUESTCLASS_H

#include <cstdint>
#include <string>
#include <QObject>

#include"PDS_protocol/pdsStruct.h"

class PalletRequestClass
{
public:

    getPalletRequest palletRequestStruct;

    PalletRequestClass();     //default: command Id - 1,pallet type - 1
    ~PalletRequestClass();
    PalletRequestClass(uint32_t commandID, uint16_t palletType);

    QByteArray ToArray();
    void ToString();
};
#endif // PALLETREQUESTCLASS_H
