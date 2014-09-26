#ifndef MASTER_DEFINITION
#define MASTER_DEFINITION

#include "bus.h"
#include "tracer.h"
#include "frame.h"
#include <unistd.h>
#include "sys/time.h"
#include "cstdlib"
#include "semaphore.h"

namespace MODBUS
{
class bus;
struct master_arguments
{
    void* context;
    bus* b;
};

class master
{
private:
    bus* bus1;
    tracer* trace;
    char* prevent_echo;
    void send_request(int);
    void wait_for_response(sem_t*);


public:
    char waiting_for;
    master(bus*, tracer*);
    void receive_data(bus* b);
    void *start(bus* b);
    static void* request_starter (void* passed)
    {
        struct master_arguments *args = (master_arguments*)passed;
        void* context = args->context;
        ((master *)context)->start(args->b);
    }
    static void* response_starter (void* passed)
    {
        struct master_arguments *args = (master_arguments*)passed;
        void* context = args->context;
        ((master *)context)->receive_data(args->b);

    }
    ~master(void);
};

}



#endif
