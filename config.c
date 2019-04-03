#include "config.h"

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
  struct Config conf  = { .justList = true, .watch = false, .rsslim = 0, .rows = 42 };

  int c;
  while(true)
  {
    int option_index = 0;
    struct option long_options[] = {
      {"rsslim",  required_argument, 0,   0  },
      {"watch",   no_argument,       0,  'w' },
      {"rows",    required_argument, 0,  'r' },
      {"help",    no_argument,       0,  'h' },
      {0,         0,                 0,   0  }
    };

    c = getopt_long(argc, (char * const *) argv, "whr:", long_options, &option_index);
    
    if(c == -1)
    {
      break;
    }

    switch (c) 
    {
      case 0:
        if(optarg)
        {
          int limit = atoi(optarg);
          conf.rsslim = limit;
        }
        break;

      case 'h':
        printHelp();
        exit(EXIT_SUCCESS);

      case 'w':
        conf.justList = false;
        conf.watch = true;
        break;

      case 'r':
        conf.rows = atoi(optarg);
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

void printConfig(struct Config conf)
{
  printf("config:\n");
  printf("just list = %d\twatch = %d\trsslim = %d\tdisplay %d rows\n", conf.justList, conf.watch, conf.rsslim, conf.rows);
}
