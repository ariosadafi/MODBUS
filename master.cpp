#include "master.h"


namespace MODBUS
{

master::master(bus* b, tracer* tr)
{
    bus1 = b;
    trace = tr;
}


void master::receive_data(bus* b)
{
    bus1 = b;
    sem_t* response = b->response;
    sem_t* request = b->request;

    long elapsed;

    while (true)
    {
        if (sem_wait(response) == 0)
        {
            frame frm = bus1->data;
            if (frm.funcode == 31)
            {
                std::cout <<  "SLAVE" << (int)frm.address << ": REG IS " << frm.data << std::endl;
                sem_post(request);
            }
            if (frm.funcode == 41)
            {
                std::cout <<  "SLAVE" << (int)frm.address << ": NOW REG IS " << frm.data << std::endl;
                sem_post(request);
            }
        }



    }
}

void master::send_request(int addr)
{
    frame frm;
    frm.address = addr;
    int what = rand()%2;
    if (what == 0)
    {
        frm.funcode = 3;
        frm.data = 1200;

        std::cout <<  "MASTER: " << (int)frm.address << " READ REG " << std::endl;
    }
    if (what == 1)
    {
        frm.funcode = 4;
        frm.data = rand()*5000;
        std::cout <<  "MASTER: " << (int)frm.address << " SET REG " << frm.data <<std::endl;

    }
    bus1->write_on_bus(frm,0);
}

void master::wait_for_response(sem_t* request)
{
    timeval start_time,finish_time;
    long elapsed;
    int semvalue;

    gettimeofday(&start_time,NULL);

    while (true)
    {
        sem_getvalue(request,&semvalue);

        if (semvalue > 0)
        {
            //finish waiting
            break;
        }
        else
        {
            gettimeofday(&finish_time,NULL);
            elapsed = ((finish_time.tv_sec - start_time.tv_sec)*1000 + (finish_time.tv_usec - start_time.tv_usec)/1000.0) + 0.5;
            if (elapsed > bus1->timeout)
            {
                std::cout << "TIME OUT" << std::endl;
                break;
            }
            usleep(100);
        }
    }
}
void *master::start(bus* b)
{
    bus1 = b;
    bus1->response = b->response;
    sem_t* request = b->request;

    int i =0;
    while(i++<bus1->slave_count*4)
    {
        sem_init(request,0,0);
        send_request(i%(bus1->slave_count + 3));
        wait_for_response(request);
        usleep(bus1->polling*1000);
    }
    exit(EXIT_SUCCESS);
}


master::~master(void)
{
}



}
