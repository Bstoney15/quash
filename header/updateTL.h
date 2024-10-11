#ifndef UPDATETL
#define UPDATETL

#include <string.h>

void updateTL(char** tl)
{
    int i = 0;

    while(strcmp(tl[i], "|") != 0)
    {
        i++;
    }
    i++; 
  
    int j = 0;
    while (tl[i] != NULL)
    {
        tl[j] = tl[i];  // Shift element
        i++;
        j++;
    }
    tl[j] = NULL;  // Set the new end of the array

}

#endif