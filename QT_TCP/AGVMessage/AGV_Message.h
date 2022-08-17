#include <cstdint>
#include <ctime>
#include "AGV_Struct.h"

typedef unsigned char byte;

struct decode {
    short head;
    short function;
    short gyro_x, gyro_y, gyro_z;
    short check;
};
//小端读取
template <typename T> // T must be integer type
T to_little_endian(T x);

//大端读取
template <typename T> // T must be integer type
T to_large_endian(T x);

uint16_t swapInt16(uint16_t value);

uint32_t swapInt32(uint32_t value);


int Crc16(byte* px, int usLen);
unsigned int Crc16(byte* px, int startIndex, int usLen);
