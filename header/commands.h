#ifndef COMMANDS
#define COMMANDS

#include <string.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#include "consts.h"

void commands(char** tl, char* currentInput, int fd)
{   

    if(tl[0] == NULL)
    {
        // free(tl[0]); 
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
                execvp("ls", tl);
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
            int isvalid = chdir(tl[1]);
            if(isvalid == -1)
            {
                printf("cd: %s: No such file or directory\n", tl[1]);
            }
            getcwd(q.cDir, sizeof(q.cDir));
        }

        return;
    }
    else if(strcmp(tl[0], "pwd") == 0)
    {
        printf("%s\n",q.cDir);

    }
    else if(strcmp(tl[0], "echo") == 0)
    {

        if(fd != -1)
        {
        dup2(fd, STDOUT_FILENO);
        close(fd);  
        }

    }
    else if(strcmp(tl[0], "export") == 0)
    {
        if(tl[1] == NULL || tl[2]== NULL){
            printf("export: error, not enough arguments \nUSAGE: export {name} {value}\n");
            return;
        }
        setenv(tl[1], tl[2], 0);
    }  
    else if(strcmp(tl[0], "cat") == 0)
    {
        int cIndex = 0;    // Index for iterating
        int isHereDoc = 0; // Flag for `<<`
        int isFileInput = 0; // Flag for `<`
        int isOutputRedir = 0; // Flag for `>` or `>>`
        int isAppend = 0;   // Flag for `>>`
        char *outputFile = NULL;

        // Check for `<<`, `<`, `>`, or `>>` in the command
        while(tl[cIndex] != NULL && strcmp(tl[cIndex], "|") != 0)
        {
            if(strcmp(tl[cIndex], "<<") == 0)
            {
                isHereDoc = 1;
                break;
            }
            else if(strcmp(tl[cIndex], "<") == 0)
            {
                isFileInput = 1;
                break;
            }
            else if(strcmp(tl[cIndex], ">") == 0)
            {
                isOutputRedir = 1;
                outputFile = tl[cIndex + 1];  // File comes after `>`
                break;
            }
            else if(strcmp(tl[cIndex], ">>") == 0)
            {
                isOutputRedir = 1;
                isAppend = 1;
                outputFile = tl[cIndex + 1];  // File comes after `>>`
                break;
            }
            cIndex++;
        }

        int status;
        int pid = fork();
        if(pid == 0)  // Child process
        {
            if(isHereDoc)
            {
                char buffer[1024];
                char *delimiter = tl[cIndex + 1];  // Delimiter comes after `<<`

                int inputFD[2];
                pipe(inputFD);

                while (1)
                {
                    printf("> ");
                    fgets(buffer, sizeof(buffer), stdin);

                    // Remove newline character from the input
                    buffer[strcspn(buffer, "\n")] = '\0';

                    // Break if the delimiter is reached
                    if(strcmp(buffer, delimiter) == 0)
                        break;

                    // Write the buffer to the pipe
                    write(inputFD[1], buffer, strlen(buffer));
                    write(inputFD[1], "\n", 1);  // Add newline after each input
                }

                close(inputFD[1]);  // Close write end after writing
                dup2(inputFD[0], STDIN_FILENO);
                close(inputFD[0]);  // Close read end after redirection
            }
            else if(isFileInput)
            {
                char *filename = tl[cIndex + 1];  // Filename comes after `<`

                // Open the file for reading
                FILE *file = fopen(filename, "r");
                if(file == NULL)
                {
                    perror("fopen failed");
                    exit(EXIT_FAILURE);
                }

                int fileFD = fileno(file);  // Get the file descriptor
                dup2(fileFD, STDIN_FILENO); // Redirect stdin to the file
                fclose(file);  // Close the file pointer, file descriptor stays open
            }

            if(isOutputRedir)
            {
                // Open the file for appending if `>>`, otherleanUpTL(curCommand);wise open for writing (`>`)
                FILE *file = fopen(outputFile, isAppend ? "a" : "w");
                if(file == NULL)
                {
                    perror("fopen failed");
                    exit(EXIT_FAILURE);
                }

                int fileFD = fileno(file);  // Get the file descriptor
                dup2(fileFD, STDOUT_FILENO); // Redirect stdout to the file
                fclose(file);  // Close the file pointer, file descriptor stays open
            }
            else if(fd != -1)
            {
                dup2(fd, STDOUT_FILENO);
                close(fd);  // Close after redirection
            }

            // Prepare arguments for `cat`
            char *args[cIndex + 1];
            args[0] = "cat";
            for (int i = 1; i < cIndex; i++)
            {
                if(strcmp(tl[i], ">") == 0 || strcmp(tl[i], ">>") == 0 || strcmp(tl[i], "<") == 0) break;
                args[i] = tl[i];
            }
            args[cIndex] = NULL;

            execvp("cat", args);
            perror("execvp failed");
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

            char* args[] = {"ls", tl[1] == NULL || strcmp(tl[1], "|") == 0 ? q.cDir : tl[1], NULL};
            execvp("ls", args);  // Using execvp for dynamic arguments

            exit(EXIT_FAILURE); 
        }
        waitpid(pid, &status, 0);
    }
    else if(strcmp(tl[0], "fg") == 0)
    {
        kill(q.jList[0].pid, 18); // for continue
        waitpid(q.jList[0].pid, NULL, 0);
    }
    else if(strcmp(tl[0], "jobs") == 0)
    {
        if(fd != -1)
        {
            dup2(fd, STDOUT_FILENO);
            close(fd);  
        }

        for(int i = 0; i < q.jobCount; i++)
        {
            printf("[%d] %d %s (%s)\n", q.jList[i].jobID, q.jList[i].pid, q.jList[i].command, q.jList[i].status);
        }
    }
    else if(strcmp(tl[0], "kill") == 0)
    {
        if(tl[1] == NULL)
        {
            printf("Kill: argument needed\n");
            return;
        }

        if(tl[1][0] == '%')
        {
            int jobId = atoi(tl[1] + 1);
            for(int i = 0; i < q.jobCount; i++)
            {
                if(q.jList[i].jobID == jobId)
                {
                    kill(q.jList[i].pid, SIGKILL);
                    return;
                }
            }
            printf("kill: job not found\n");

        }
    }
    else
    {
        int status;
        pid_t pid = fork();
        if(pid == 0)
        {

            if(strcmp(currentInput, "") != 0)
            {
                int inputFD[2];
                pipe(inputFD);

                write(inputFD[1], currentInput, strlen(currentInput));
                close(inputFD[1]); 

                dup2(inputFD[0], STDIN_FILENO);
                close(inputFD[0]); 
            }
            if(fd != -1)
            {
                dup2(fd, STDOUT_FILENO);
                close(fd);  
            }


            execvp(tl[0], tl);
            perror("QUASH: command execution failed");
            fprintf(stderr, "QUASH: unknown command: %s\n", tl[0]);
            exit(0);
        }
        waitpid(pid, &status, 0);
    }


}

#endif