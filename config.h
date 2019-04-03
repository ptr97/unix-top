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
  unsigned int rows;
};


void printHelp();
struct Config readConfig(int argc, const char * argv[]);
void printConfig(struct Config conf);


#endif
