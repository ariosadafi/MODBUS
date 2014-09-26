#pragma once
#include "tracer.h"
#include "frame.h"
#include "bus.h"


namespace MODBUS
{
class bus;
class slave
{
private:
    tracer* trace;
    int id;
    bus* bus1;
    int reg;

    void handle_frame(frame);

public:
    slave(int, bus* ,tracer*, int);
    void receive_data(frame);
    void send_response(frame);
    ~slave(void);
};

}
