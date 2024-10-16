#ifndef STRSPLIT
#define STRSPLIT

#include <string.h>
#include <stdio.h>

void strSplit(char* input, char* tl[])
{
    char* token;
    int tc = 0;

    token = strtok(input, " \n");
    if(token == NULL)
    {
        tl[0] = NULL;
        return;
    }

    while (token != NULL)
    {
        tl[tc] = token;
        tc++;
        token = strtok(NULL, " \n"); 
    }

    tl[tc] = NULL;
    return;
    
}


#endif
