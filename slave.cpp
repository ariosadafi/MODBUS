#include "slave.h"

namespace MODBUS
{
slave::slave(int slaveID, bus* b, tracer* tr,int registerValue)
{
    id = slaveID;
    bus1 = b;
    trace = tr;
    reg = registerValue;
}

void slave::receive_data(frame frm)
{

    if (frm.address == id)
    {
//			std::cout <<  (int)id << " : " << frm.data << std::endl;
 //       if (frm.funcode == 2) send_response();
            handle_frame(frm);

    }
}


void slave::handle_frame(frame frm)
{
    frame res;
    if (frm.funcode == 3)
    {
        res.address = frm.address;
        res.data = reg;
        res.funcode = 31;
        send_response(res);
    }
    else if (frm.funcode == 4)
    {
        res.address = frm.address;
        reg = frm.data;
        res.data = reg;
        res.funcode = 41;
        send_response(res);
    }


}

void slave::send_response(frame frm)
{
     bus1->write_on_bus(frm, 1);
}

slave::~slave(void)
{
}

}
