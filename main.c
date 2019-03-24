#include <stdio.h>
#include "config.h"


int main(int argc, const char * argv[])
{
    struct Config conf = readConfig(argc, argv);

    return 0;
}
