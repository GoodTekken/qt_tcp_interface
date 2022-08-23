#ifndef FUNCTION_H
#define FUNCTION_H

#include <QObject>
//#include <QMutex>
//#include <QSharedPointer>

void string_to_hex(QString hex,QByteArray &qbyte);

QByteArray convertUInt32ToByte(uint32_t data);
QByteArray convertUInt16ToByte(uint16_t data);

//小端读取
template <typename T> // T must be integer type
T to_little_endian(T x);

//大端读取
template <typename T> // T must be integer type
T to_large_endian(T x);

uint16_t swapUInt16(uint16_t value);

uint32_t swapUInt32(uint32_t value);

int32_t swapInt32(int32_t value);

float Byte2Float(QByteArray byte);

void reverseByte(QByteArray &arrayToChange,uint32_t start,uint32_t end);
#endif // FUNCTION_H
