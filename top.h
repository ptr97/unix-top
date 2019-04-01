#ifndef __PROCESSES_READER_H__
#define __PROCESSES_READER_H__

#include <glob.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/procfs.h>

#define MAX_BUFF_SIZE 4096

// uid() - for check if there is my own process


typedef struct statstruct_proc {
	int           pid;
	char          exName[MAX_BUFF_SIZE];
	char          state;
	int           euid,                     /** %d effective user id **/
								egid;                     /** %d effective group id */					     
	int           ppid;                     /** %d The pid of the parent. **/
	int           pgrp;                     /** %d The pgrp of the process. **/
	int           session;                  /** %d The session id of the process. **/
	unsigned long tty;                      /** %lu The tty the process uses **/
	unsigned long tpgid;                    /** %lu  **/
	unsigned long	flags;                    /** %lu The flags of the process. **/
	unsigned long	minflt;                   /** %lu The number of minor faults **/
	unsigned long	cminflt;                  /** %lu The number of minor faults with childs **/
	unsigned long	majflt;                   /** %lu The number of major faults **/
	unsigned long cmajflt;                  /** %lu The number of major faults with childs **/
	long          utime;                    /** %ld user mode jiffies **/
	long          stime;                    /** %ld kernel mode jiffies **/
	long          cutime;                   /** %ld user mode jiffies with childs **/
	long          cstime;                   /** %ld kernel mode jiffies with childs **/
	long          counter;                  /** %ld process's next timeslice **/
	long          priority;                 /** %ld the standard nice value, plus fifteen **/
	unsigned long timeout;                  /** %lu The time in jiffies of the next timeout **/
	unsigned long itrealvalue;              /** %lu The time before the next SIGALRM is sent to the process **/
	long          starttime;                /** %ld Time the process started after system boot **/
	unsigned long vsize;                    /** %lu Virtual memory size **/
	unsigned long rss;                      /** %lu Resident Set Size **/
	unsigned long rlim;                     /** %lu Current limit in bytes on the rss **/
	unsigned long startcode;                /** %lu The address above which program text can run **/
	unsigned long	endcode;                  /** %lu The address below which program text can run **/
	unsigned long startstack;               /** %lu The address of the start of the stack **/
	unsigned long kstkesp;                  /** %lu The current value of ESP **/
	unsigned long kstkeip;                  /** %lu The current value of EIP **/
	unsigned long	signal;                   /** %lu The bitmap of pending signals **/
	unsigned long blocked;                  /** %lu The bitmap of blocked signals **/
	unsigned long sigignore;                /** %lu The bitmap of ignored signals **/
	unsigned long sigcatch;                 /** %lu The bitmap of catched signals **/
	unsigned long wchan;                    /** %lu **/
} ProcessStat;



void printProgramHeader()
{
	printf("<-------------------- UNIX top by Piotr Wos -------------------->\n\n");
}

void printProcessesInfoHeader()
{
	printf("   PID  USER     PR  NI    VIRT     RES    S       COMMAND   \n");
	// printf("   PID  USER     PR  NI    VIRT     RES    SHR  S    %%CPU    %%MEM     TIME+    COMMAND   \n");
}

void printProcessInfo(ProcessStat stat, unsigned int rssLimit)
{
	if(stat.rss > rssLimit)
		printf("%6d  piotr   %3ld %3ld  %6ld  %6ld  %3c  %12s\n", stat.pid, stat.priority + 20, stat.priority, stat.vsize/1024, stat.rss, stat.state, stat.exName);
}


void readAllProcesses(unsigned int rssLimit)
{
	FILE * fp = NULL;
	char * s, * t;
	char statBuffor[2048];
	glob_t globbuf;

	glob("/proc/[0-9]*/stat", 0, NULL, &globbuf);

	for(size_t i = 0; i < globbuf.gl_pathc; ++i)
	{
		const char * fileName = globbuf.gl_pathv[i];

		if((fp = fopen(fileName, "r")) == NULL) 
		{
			printf("ERROR: %s open failed\n", fileName);
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

		printProcessInfo(processStat, rssLimit);

		fclose(fp);
	}

	globfree(&globbuf);
}


#endif
