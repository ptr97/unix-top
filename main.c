#include <stdio.h>
#include "config.h"
#include "top.h"


int main(int argc, const char * argv[])
{
  struct Config conf = readConfig(argc, argv);
  printProgramHeader();
  printProcessesInfoHeader();
  
  readAllProcesses();

  return 0;
}
