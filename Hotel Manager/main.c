#include <stdio.h>
#include <stdlib.h>

//#define DEBUG

#ifndef DEBUG
    #include "display.h"
    #include "record.h"
    #include "room.h"
    #include "util.h"
#endif

int main()
{
    window();
    return 0;
}
