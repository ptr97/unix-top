#include "top.h"


void clearScreen()
{
  printf("\e[1;1H\e[2J");
}

void printProgramHeader()
{
	printf("%s", MAG);
	printf("<------------------------------ UNIX top by Piotr Wos ------------------------------>\n\n");
	printf("%s", RESET);
}

void printProcessesInfoHeader()
{
	printf("%s", CYN);
	printf("%6s\t%6s\t%6s\t%12s\t%12s\t%3s\t%12s\n", "PID", "PR", "NI", "VIRT", "RES", "S", "COMMAND");
	printf("%s", RESET);
	// oryginal TOP header -> PID USER PR NI VIRT RES SHR S %CPU %MEM TIME+ COMMAND
}

void printProcessInfo(ProcessStat stat, unsigned int rssLimit)
{
	if(stat.rss > rssLimit)
		printf("%6d\t%6ld\t%6ld\t%12ld\t%12ld\t%3c\t%-12s\n", stat.pid, stat.priority + 20, stat.priority, stat.vsize/1024, stat.rss, stat.state, stat.exName);
}

int compare(const void * a, const void * b)
{
	ProcessStat * ptrA = (ProcessStat *) a;
	ProcessStat * ptrB = (ProcessStat *) b;

	return (ptrB->rss - ptrA->rss);
}


void readAllProcesses(unsigned int rssLimit, unsigned int rows)
{
	FILE * fp = NULL;
	char * s, * t;
	char statBuffor[2048];
	glob_t globbuf;

	glob("/proc/[0-9]*/stat", 0, NULL, &globbuf);
	ProcessStat * arrayOfProcesses = calloc(globbuf.gl_pathc, sizeof(ProcessStat));

	for(size_t i = 0; i < globbuf.gl_pathc; ++i)
	{
		const char * fileName = globbuf.gl_pathv[i];

		if((fp = fopen(fileName, "r")) == NULL) 
		{
			fprintf(stderr, "ERROR: %s open failed\n", fileName);	
			continue;
		}

		if((s = fgets(statBuffor, 2048, fp)) == NULL) 
		{
			fclose(fp);
			continue;
		}

		ProcessStat processStat;
		memset(&processStat, 0, sizeof(processStat));
		
		sscanf (statBuffor, "%u", &(processStat.pid));
		s = strchr(statBuffor, '(') + 1;
		t = strchr(statBuffor, ')');
		strncpy(processStat.exName, s, t - s);
		processStat.exName[t - s] = '\0';
		sscanf(t + 2, "%c %d %d %d %ld %ld %lu %lu %lu %lu "
			/*      1  2  3  4  5  6  7   8   9   10 */
			"%lu %lu %lu %ld %ld %ld %ld %lu %ld %lu "
			/*11	12  13  14  15  16  17  18  19  20  */
			"%lu %ld %lu %lu %lu %lu %lu %lu %lu %lu "
			/*21	22	23	24	25	26	27	28	29	30 */
			"%lu %lu %lu",
			/*31	32	33 */
			&(processStat.state),
			&(processStat.ppid),
			&(processStat.pgrp),
			&(processStat.session),
			&(processStat.tty),
			&(processStat.tpgid),
			&(processStat.flags),
			&(processStat.minflt),
			&(processStat.cminflt),
			&(processStat.majflt),
			&(processStat.cmajflt),
			&(processStat.utime),
			&(processStat.stime),
			&(processStat.cutime),
			&(processStat.cstime),
			&(processStat.counter),
			&(processStat.priority),
			&(processStat.timeout),
			&(processStat.itrealvalue),
			&(processStat.starttime),
			&(processStat.vsize),
			&(processStat.rss),
			&(processStat.rlim),
			&(processStat.startcode),
			&(processStat.endcode),
			&(processStat.startstack),
			&(processStat.kstkesp),
			&(processStat.kstkeip),
			&(processStat.signal),
			&(processStat.blocked),
			&(processStat.sigignore),
			&(processStat.sigcatch),
			&(processStat.wchan)
		);

		arrayOfProcesses[i] = processStat;

		fclose(fp);
	}

	qsort(arrayOfProcesses, globbuf.gl_pathc, sizeof(ProcessStat), compare);

	for(size_t j = 0; j < rows && j < globbuf.gl_pathc; ++j)
	{
		printProcessInfo(arrayOfProcesses[j], rssLimit);
	}

	free(arrayOfProcesses);

	globfree(&globbuf);
}
