#ifndef FUNCTION_H
#define FUNCTION_H

#include <QObject>
//#include <QMutex>
//#include <QSharedPointer>

void string_to_hex(QString hex,QByteArray &qbyte);

QByteArray convertUInt32ToByte(uint32_t data);
QByteArray convertUInt16ToByte(uint16_t data);

#endif // FUNCTION_H
