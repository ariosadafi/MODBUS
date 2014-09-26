// MODBUS001.cpp : Defines the entry point for the console application.
//



#include "string"
#include "MODBUSSimulator.h"
#include "iostream"

int main(int argc, char* argv[])
{

	std::string path = std::string("test.conf");

	if (argc >= 2) 
		path = std::string(argv[1]);		

	MODBUS::MODBUSSimulator simulator(path);
	simulator.start();


	return 0;
}

