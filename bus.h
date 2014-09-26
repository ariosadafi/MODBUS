#ifndef BUS_DEFINITION
#define BUS_DEFINITION


#include "master.h"
#include "slave.h"
#include "tracer.h"
#include "semaphore.h"

namespace MODBUS
{


#define MASTER_UNIQUE_EXCEPTION 23
#define MAXIMUM_SLAVE_EXCEPTION 23
#define ERROR_OVERFLOW 23

const int MAX_SLAVE_COUNT = 10;
const int MAX_DATA_LEN   = 256;

};



namespace MODBUS
{
class master;
class slave;
class bus
{

public:
    frame data;
    slave** slaves;
    master* mstr;
    tracer* trace;
    int slave_count;
    void propagate(int);
    long polling;
    long timeout;

public:
    bus(tracer*);
    int write_on_bus(frame, int);
    void connect(slave*);
    void connect(master*);
    sem_t* response;
    sem_t* request;
    ~bus(void);
};
}

#endif
