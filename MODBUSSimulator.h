#pragma once


#include "master.h"
#include "slave.h"
#include "bus.h"
#include "tracer.h"
#include "pthread.h"
#include "string"
#include "semaphore.h"
#include "fstream"
#include "cstring"




namespace MODBUS
{

class MODBUSSimulator
{

private:
    int slave_count;
    master* mstr;
    slave** slaves;
    bus* bus1;
    tracer* trace;
    sem_t* response;
    sem_t* request;
    long polling;
    long timeout;


public:
    MODBUSSimulator(const std::string);
    ~MODBUSSimulator(void);
    void start();
    int init(int*);
};

};
