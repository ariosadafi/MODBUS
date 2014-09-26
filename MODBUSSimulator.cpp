#include "MODBUSSimulator.h"


namespace MODBUS
{

MODBUSSimulator::MODBUSSimulator(const std::string filestr)
{
    //TODO: read input file fill in the data
    std::ifstream reader;
    char token[200];
    int* regArray;

    reader.open(filestr.c_str());
    if (reader.is_open())
    {
        while(!reader.eof())
        {
            reader >> token;
            if (!strcmp(token,"POLLING"))
            {
                reader >> token;
                polling = atoi(token);
            }
            else if (!strcmp(token,"TIMEOUT"))
            {
                reader >> token;
                timeout = atoi(token);
            }
            else if (!strcmp(token,"SLAVE_COUNT"))
            {
                reader >> token;
                slave_count = atoi(token);
                regArray = new int[slave_count];

                for (int i = 0; i < slave_count; i++)
                {
                    reader >> token;
                    reader >> token;
                    regArray[i] = atoi(token);
                }
            }

        }

    }
    else
    {
        std::cout << "Configuration file not found. \n";
        exit(1);
    }

    init(regArray);

}


MODBUSSimulator::~MODBUSSimulator(void)
{


}

void MODBUSSimulator::start()
{
    pthread_t master_response;
    pthread_t master_request;
    int err;
    master_arguments args;
    args.context = &mstr;
    response = new sem_t();
    request = new sem_t();
    sem_init(response,0,0);
    sem_init(request,0,0);
    bus1->response = response;
    bus1->request = request;
    bus1->polling = polling;
    bus1->timeout = timeout;
    args.b = bus1;

    err = pthread_create(&master_request, NULL, &master::request_starter, &args);

    if(err)
    {
        std::cout<<"Error";
        return;
    }
    err = pthread_create(&master_response, NULL, &master::response_starter, &args);

    if(err)
    {
        std::cout<<"Error";
        return;
    }
    pthread_join( master_request, NULL);
    pthread_join( master_response, NULL);
    exit(EXIT_SUCCESS);
}


int MODBUSSimulator::init(int* reg_list)
{

    trace = new tracer();
    bus1 = new bus(trace);
    slaves = new slave*[slave_count];
    for (int i = 0; i < slave_count; i++)
        slaves[i] = new slave(i,bus1,trace,reg_list[i]);
    mstr = new master(bus1,trace);


    bus1->connect(mstr);
    for (int i = 0; i < slave_count; i++)
        bus1->connect(slaves[i]);

    return 0;
}
}

