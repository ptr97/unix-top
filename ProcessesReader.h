#ifndef __PROCESSES_READER_H__
#define __PROCESSES_READER_H__

#include <glob.h>

// uid() - for check if there is my own process 


void readProcesses()
{
	glob_t globbuf;
	glob("/proc/[0-9]*/stat", NULL, NULL, &globbuf);

	for(size_t i = 0; i < globbuf.gl_pathc; ++i)
	{
		printf("%s\n", globbuf.gl_pathv[i]);
	}

	// remember to free globbuf!

}


#endif
