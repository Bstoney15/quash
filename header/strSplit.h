#ifndef STRSPLIT
#define STRSPLIT

#include <string.h>
#include <stdio.h>

void strSplit(char* input, char* tl[])
{
    char* token;
    int tc = 0;

    token = strtok(input, " \n");
    while (token != NULL)
    {
        tl[tc] = token;
        tc++;
        token = strtok(NULL, " \n");  // Use NULL instead of input
    }

    tc++;
    tl[tc] = NULL;
    return;
    
}


#endif
