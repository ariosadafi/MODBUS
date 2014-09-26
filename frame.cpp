#include "frame.h"

namespace MODBUS
{
frame::frame(void)
{

//    crc = new char[2]; // 16 bit crc
}

frame::frame(char* serial)
{
    address = serial[0];
    funcode = serial[1];
    data = *(uint16_t*)serial + 2;
}


void frame::setdata(uint16_t dt, char addr, char function)
{
    funcode = function;
    address = addr;
    data = dt;
    //calculate CRC here
}


frame::~frame(void)
{
}
}
