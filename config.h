#ifndef __CONFIG_H__
#define __CONFIG_H__

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <unistd.h>
#include <getopt.h>


struct Config
{
  bool justList;
  bool watch;
  unsigned int rsslim;
};

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

struct Config readConfig(int argc, const char * argv[])
{
  struct Config conf  = { .justList = true, .watch = false, .rsslim = 0 };

  int c;
  while(true)
  {
    int option_index = 0;
    struct option long_options[] = {
      {"rsslim",  required_argument, 0,   0  },
      {"watch",   no_argument,       0,  'w' },
      {"help",    no_argument,       0,  'h' },
      {0,         0,                 0,   0  }
    };

    c = getopt_long(argc, (char * const *) argv, "wh", long_options, &option_index);
    
    if(c == -1)
    {
      break;
    }

    switch (c) 
    {
      case 0:
        printf("option %s", long_options[option_index].name);
        if(optarg)
        {
          printf(" with arg %s\n", optarg);
          int limit = atoi(optarg);
          conf.rsslim = limit;
          printf("limit = %d\n", limit);
        }
        printf("\n");
        break;

      case 'h':
        printHelp();
        exit(EXIT_SUCCESS);

      case 'w':
        conf.justList = false;
        conf.watch = true;
        printf("--watch mode\njustList = %d\tconf.watch = %d\n", conf.justList, conf.watch);
        break;

      case '?':
        break;

      default:
        printf("?? getopt returned character code 0%o ??\n", c);
    }
  }

  if (optind < argc) 
  {
    printf("not supported parameters: ");
    while (optind < argc)
      printf("%s ", argv[optind++]);
    printf("\n");
  }

  return conf;
}


#endif
