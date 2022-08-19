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



int Crc16(byte* px, int usLen);
unsigned int Crc16(byte* px, int startIndex, int usLen);
