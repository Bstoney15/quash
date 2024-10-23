#ifndef UPDATETL
#define UPDATETL

#include <string.h>


char** updateTL(char** tl)
{
    int i = 0;
    
    // Count tokens up to the first pipe
    while (tl[i] != NULL && strcmp(tl[i], "|") != 0)
    {
        i++;
    }

    // Allocate memory for the first command and its arguments
    char** firstCommand = (char**)malloc((i + 1) * sizeof(char*));
    
    // Copy the first command and its arguments into the new list
    for (int j = 0; j < i; j++)
    {
        firstCommand[j] = tl[j];
    }
    firstCommand[i] = NULL;  // Null-terminate the first command array

    // If a pipe was found, update tl to start after the pipe
    if (tl[i] != NULL && strcmp(tl[i], "|") == 0)
    {
        i++;  // Move past the pipe
        int j = 0;
        while (tl[i] != NULL)
        {
            tl[j] = tl[i];  // Shift the remaining tokens
            i++;
            j++;
        }
        tl[j] = NULL;  // Null-terminate the updated token list
    }
    else
    {
        tl[0] = NULL;  // No more commands, reset the token list
    }

    // Return the first command and its arguments
    return firstCommand;
}



#endif