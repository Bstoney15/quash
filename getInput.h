#ifndef GETINPUT
#define GETINPUT

#include <stdio.h>
#include <string.h>

void getInput(char* input)
{
    printf("[QUASH]: - $:");
	fgets(input, 255, stdin);
    return;
}

#endif