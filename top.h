#ifndef __PROCESSES_READER_H__
#define __PROCESSES_READER_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <glob.h>
#include <fcntl.h>
#include <errno.h>

#define MAX_BUFF_SIZE 4096

#define RED   "\x1B[31m"
#define GRN   "\x1B[32m"
#define YEL   "\x1B[33m"
#define BLU   "\x1B[34m"
#define MAG   "\x1B[35m"
#define CYN   "\x1B[36m"
#define WHT   "\x1B[37m"
#define RESET "\x1B[0m"


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


void clearScreen();
void printProgramHeader();
void printProcessesInfoHeader();
void printProcessInfo(ProcessStat stat, unsigned int rssLimit);
int compare(const void * a, const void * b);
void readAllProcesses(unsigned int rssLimit, unsigned int rows);


#endif
