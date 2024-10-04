#ifndef COMMANDS
#define COMMANDS

#include <string.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>

#include "consts.h"

void commands(char** tl)
{   
    if(tl[0] == NULL)
    {
        return;
    }



    if(strcmp(tl[0], "exit") == 0 || strcmp(tl[0], "quit") == 0)
    {
        q.isRunning = 0;
    }
    else if(strcmp(tl[0], "clear") == 0)
    {
        system("clear");
    }
    else if(strcmp(tl[0], "ls") == 0)
    {   
        int status;
        int pid = fork();
        if(pid == 0)
        {
            execl("/bin/ls", "-l", NULL);
            exit(0); 
        }
        wait(&status);	
    }
    else if(strcmp(tl[0], "pwd") == 0)
    {
        printf(q.cDir);

    }
    else
    {
        printf("QUASH: unknown command\n");
    }
}


#endif
