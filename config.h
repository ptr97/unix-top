#ifndef __CONFIG_H__
#define __CONFIG_H__

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

struct Config
{
    bool justList;
    bool watch;
    unsigned int rsslim;
};

bool stringEqual(const char * str1, const char * str2)
{
    return strcmp(str1, str2) == 0;
}

bool stringStartsWith(const char * str, const char * prefix)
{
    return strncmp(str, prefix, strlen(prefix)) == 0;
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
    struct Config conf  = { .justList = true, .watch = false, .rsslim = 0 };
    if(args > 1)
    {
        if(stringEqual(argv[1], "--help"))
        {
            printHelp();
            exit(EXIT_SUCCESS);
        }
        
        for(unsigned i = 1; i < args; ++i)
        {
            if(stringEqual(argv[i], "--watch"))
            {
                conf.justList = false;
                conf.watch = true;
            }
            else if(stringStartsWith(argv[i], "--rsslim="))
            {
                int limit = atoi(argv[i] + strlen("--rsslim="));
                conf.rsslim = limit;
            }
            else
            {
                printf("%s is not valid flag.\n", argv[i]);
                exit(EXIT_FAILURE);
            }                
        }
    }
    return conf;
}


#endif
