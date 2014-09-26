===================================================================================================
MODBUS SIMULATOR
===================================================================================================

This simulator reads the configuration file and creates the slaves and master according to it. Afterwards the server starts generating random commands which are either requests to read the register in an address or writing a random value to it.


---------------------------------------------------------------------------------------------------
  COMPILING THE SOURCE CODE
---------------------------------------------------------------------------------------------------
In order to compile the source codes, change directory to the folder holding source files and use G++ to compile all of the files headers and sources.
For creating the threads of simulator, PTHREAD library is used and must be linked to the project using -pthread directive.
typing the following commad would do the task.

g++ -w -pthread -o sim *.h *.cpp

---------------------------------------------------------------------------------------------------
  CONFIGURATION FILE
---------------------------------------------------------------------------------------------------
Configuration file is a text file holding made of 3 sections.
1- POLLING INTERVAL: the keyword "POLLING" followed with a long-int indicating the interval in milliseconds that server sends requests to different slaves.
2- TIMEOUT: the keyword "TIMEOUT" followed by a long-int which indicates the time in milliseconds before server gives up waiting for a slave to respond.
3- SLAVE DETAILS: the keyword "SLAVE_COUNT" followed by an integer number indicating the number of slaves which are supposed to connect to the bus. Then after this line each slave address and register value is proposed.

* It is clear that the value of POLLING should be bigger than TIMEOUT to avoid conflicts.
** The user should take care of consistancy between the number of slaves introduced and the (address - register) couples followed by it.

Here is a sample of configuration file:

POLLING 1000
TIMEOUT 100
SLAVE_COUNT 5
0	100
1	300
2	500
3	1014
4	100



---------------------------------------------------------------------------------------------------
  RUNNING THE SIMULATOR
---------------------------------------------------------------------------------------------------
If an argument is passed to the simulator it will try to look for the file path mentioned in the argument, otherwise it will search for "test.conf" file in the same directory. 
The simulator does not run without a configuration file.


---------------------------------------------------------------------------------------------------
  SIMULATOR BEHAVIOUR
---------------------------------------------------------------------------------------------------
When started, master node starts sending random commands to slaves which are present. In addition to it, it tries to contact some more slaves that we know are not present in order to demonstrate the timeout mechanism. random commands are either request to read the register value from a slave or a request to slave to set its register to the value specified by the master which is random as well.
Server prints to the console requests sent and responses received. For the above configuration file a truncated simulation output would be the following:

./sim
1:	BUS: master connected
2:	BUS: slave connected
3:	BUS: slave connected
4:	BUS: slave connected
5:	BUS: slave connected
6:	BUS: slave connected
MASTER: 1 SET REG 45872
SLAVE1: NOW REG IS 45872
MASTER: 2 SET REG 1560
SLAVE2: NOW REG IS 1560
MASTER: 3 SET REG 21624
SLAVE3: NOW REG IS 21624
MASTER: 4 READ REG 
SLAVE4: REG IS 100
MASTER: 5 READ REG 
TIME OUT
MASTER: 6 SET REG 33768
TIME OUT
MASTER: 7 READ REG 
TIME OUT
MASTER: 0 SET REG 65168
SLAVE0: NOW REG IS 65168
MASTER: 1 SET REG 6552
SLAVE1: NOW REG IS 6552
MASTER: 2 READ REG 
SLAVE2: REG IS 1560
.
.
.


