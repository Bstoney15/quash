#ifndef COUNT_PIPES
#define COUNT_PIPES

#include <string.h>
#include <stdio.h>

int countPipes(char** tl)
{
    int count = 0;
    int i = 0;


    while(tl[i] != NULL)
    {
        if(strcmp(tl[i], "|") == 0)
        {
            count++; 
        }
        i++;
    }

    return count;

}




#endif
