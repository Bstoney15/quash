#ifndef COMMANDS
#define COMMANDS

#include <string.h>
#include <stdio.h>

#include "consts.h"

void commands(char** tl)
{   
    if(tl[0] == NULL)
    {
        return;
    }



    if(strcmp(tl[0], "exit") == 0)
    {
        isRunning = 0;
    }
    else if(strcmp(tl[0], "clear") == 0)
    {
        system("clear");
    }
    else
    {
        printf("QUASH: unknown command\n");
    }
}


#endif