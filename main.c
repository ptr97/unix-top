#include <stdio.h>
#include "config.h"
#include "ProcessesReader.h"


int main(int argc, const char * argv[])
{
  struct Config conf = readConfig(argc, argv);

  // cglob - for scanning directory 
  readProcesses();

  return 0;
}
