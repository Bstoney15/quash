#ifndef COMMANDS
#define COMMANDS

#include <string.h>
#include <stdio.h>

#include "consts.h"

void commands(char** tl)
{
    if(strcmp(tl[0], "exit") == 0)
    {
        isRunning = 0;
    }
    else if(strcmp(tl[0], "place") == 0)
    {
        
    }
    else
    {
        printf("QUASH: unknown command\n");
    }
}


#endif