#include <stdio.h>
#include "config.h"
#include "top.h"


int main(int argc, const char * argv[])
{
	struct Config conf = readConfig(argc, argv);
	printProgramHeader();
	
	printProcessesInfoHeader();
	readAllProcesses(conf.rsslim, conf.rows);

	while(conf.watch) 
	{
		clearScreen();
		printProcessesInfoHeader();
		readAllProcesses(conf.rsslim, conf.rows);
		sleep(2);
	}

	return 0;
}
