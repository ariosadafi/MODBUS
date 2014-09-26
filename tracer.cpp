#include "tracer.h"

namespace MODBUS
{

tracer::tracer(void)
{
    line_num = 1;
}

void tracer::status(char* sts)
{
    std::cout << line_num++ << ":\t" << sts << std::endl;
}
tracer::~tracer(void)
{
}


}
