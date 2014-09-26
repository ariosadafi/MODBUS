#include "iostream"
#pragma once

namespace MODBUS
{

class tracer
{
private:
    int line_num;
public:
    tracer(void);
    void status(char*);
    ~tracer(void);
};

}
