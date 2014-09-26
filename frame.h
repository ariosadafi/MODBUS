#include "iostream"
#include <string>
#include "inttypes.h"
#pragma once
namespace MODBUS
{
class frame
{
public:
    char funcode;
    char address;
    uint16_t data;
    uint16_t crc;

public:
    frame(void);
    frame(char*);
    ~frame(void);
    void setdata(uint16_t, char,char );
    char* serialize();


};

}
