#ifndef __CONFIG_H__
#define __CONFIG_H__

#include <stdio.h>
#include <stdbool.h>
#include <string.h>

struct Config
{
    bool help;
    bool justList;
    bool watch;
    unsigned int rsslim;
};

bool stringEqual(const char * str1, const char * str2)
{
    return strcmp(str1, str2) == 0;
}

void printHelp()
{
    printf("mytop unix program\n");
    printf("usage: ./mytop\n");
    printf("\t\t[<no args>]\t -> snapshot of processes\n");
    printf("\t\t[--watch]\t -> keeps running and listing processes\n");
    printf("\t\t[--rsslim=10M]\t -> listing processes that exceed RSS limit of 10M\n");
    printf("\t\t[--help]\t -> display functionality\n");
    printf("\nauthor: Piotr Wos\n");
}

struct Config readConfig(int args, const char * argv[])
{
    struct Config conf  = { .help = false, .justList = true, .watch = false, .rsslim = 0 };
    if(args > 1)
    {
        if(stringEqual(argv[1], "--help"))
        {
            printHelp();
        }
    }
    return conf;
}


#endif
