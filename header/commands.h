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

            if(tl[1] == NULL)
            {
            execl("/bin/ls", "ls", q.cDir, NULL);

            exit(0); 
            }
            else
            {
                char cmdbuf[BSIZE];
                sprintf(cmdbuf, "%s/%s", q.cDir, tl[1]);
                execl("/bin/ls", "ls", cmdbuf, NULL);
            }

            exit(0); 
        }

        waitpid(pid, &status, 0);
    }
    else if(strcmp(tl[0], "cd") == 0)
    {
        if(tl[1] == NULL)
        {
            printf("cd: expected argument\n");
            return;
        }
        
        char newPath[BSIZE];
        snprintf(newPath, sizeof(newPath), "/%s", tl[1]);
        strcat(q.cDir, newPath); 

        chdir(tl[1]);

        return;
    }
    else
    {
        printf("QUASH: unknown command\n");
    }
}


#endif
