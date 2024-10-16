#ifndef COMMANDS
#define COMMANDS

#include <string.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>

#include "consts.h"

void commands(char** tl, char* currentInput, int fd)
{   

    if(tl[0] == NULL)
    {
        return;
    }
    else if(strcmp(tl[0], "exit") == 0 || strcmp(tl[0], "quit") == 0)
    {
        q.isRunning = 0;
        return;
    }
    
    
    if(strcmp(tl[0], "clear") == 0)
    {
        system("clear");
        exit(0);
    }
    else if(strcmp(tl[0], "grep") == 0)
    {
        int status;

        int pid = fork();
        if(pid == 0)  // Child process
        {
            // If fromProcess is not an empty string, pass it as input to grep
            if(strcmp(currentInput, "") != 0)
            {
                int inputFD[2];
                pipe(inputFD);

                write(inputFD[1], currentInput, strlen(currentInput));
                close(inputFD[1]);  // Close write end after writing

                dup2(inputFD[0], STDIN_FILENO);
                close(inputFD[0]); 
            }

    
            if(fd != -1)
            {
                dup2(fd, STDOUT_FILENO);
                close(fd);  // Close after redirection
            }

            execl("/bin/grep", "grep", tl[1], NULL);

            perror("execl failed");
            exit(EXIT_FAILURE);
        }

        waitpid(pid, &status, 0);
    }
    else if(strcmp(tl[0], "ls") == 0)
    {   
        int status;
        int pid = fork();
        if(pid == 0)
        {   

            if(fd != -1)
            {
                dup2(fd, STDOUT_FILENO);
                close(fd);
            }
            

            if(tl[1] == NULL || strcmp(tl[1], "|") == 0)
            {
                execl("/bin/ls", "ls", q.cDir, NULL);

                exit(0); 
            }
            else
            {
                char cmdbuf[BSIZE];
                sprintf(cmdbuf, "%s/%s", q.cDir, tl[1]);
                execl("/bin/ls", "ls", cmdbuf, NULL);

                exit(0); 
            }

        }

        waitpid(pid, &status, 0);
    }
    else if(strcmp(tl[0], "cd") == 0)
    {
        if(tl[1] == NULL)
        {
            printf("cd: expected argument\n");
            
        }
        else
        {
            chdir(tl[1]);
            getcwd(q.cDir, sizeof(q.cDir));
        }

        return;
    }
    else if(strcmp(tl[0], "pwd") == 0)
    {
        printf("%s\n",q.cDir);

    }
    else
    {
        printf("QUASH: unknown command: %s\n", tl[0]);
    }

    
    }




#endif
