#ifndef PDSPALLETRESPONSECLASS_H
#define PDSPALLETRESPONSECLASS_H
#include <cstdint>
#include <string>
#include <QObject>
#include"PDS_protocol/pdsStruct.h"

class pdsPalletResponseClass
{
public:
    getPalletResponse_success palletResponseSuccessStruct;
    getPalletResponse_failure palletResponseFailureStruct;
    pdsPalletResponseClass();
    ~pdsPalletResponseClass();

    void response_failure(uint32_t commandID,int32_t errorCode);
    QByteArray ToFailureArray();

    pdsPalletResponseClass(QByteArray array);
    void ToString();
};

#endif // PDSPALLETRESPONSECLASS_H
