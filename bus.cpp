#include "bus.h"


namespace MODBUS
{

bus::bus(tracer* tr)
{
    //initialize slaves array with MAX_SLAVE_COUNT
    slaves = new slave*[MODBUS::MAX_SLAVE_COUNT];
    for (int i = 0; i < MODBUS::MAX_SLAVE_COUNT; i++)
        slaves[i] = NULL;

    //initialize data array
    data = new char[MAX_DATA_LEN];
    trace = tr;
    slave_count = 0;

}

void bus::connect(slave* s)
{

    if (slave_count < MAX_SLAVE_COUNT)
    {
        slaves[slave_count++] = s;

        trace->status("BUS: slave connected");
    }
    else
        throw MAXIMUM_SLAVE_EXCEPTION;

}

void bus::connect(master* m)
{
    static int master_max = 1;
    if (master_max > 0)
    {
        mstr = m;
        master_max--;
        trace->status("BUS: master connected");
    }
    else
        throw MASTER_UNIQUE_EXCEPTION;

}

int bus::write_on_bus(frame frm, int ms)
{
    //delete data;
    data = frm;
    propagate(ms);
    return true;
}

void bus::propagate(int ms)
{
    for(int i = 0; i < slave_count; i++)
        slaves[i]->receive_data(data);
    if (ms) sem_post(response);
}


bus::~bus(void)
{
}

};
