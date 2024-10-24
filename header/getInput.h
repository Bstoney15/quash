#ifndef GETINPUT
#define GETINPUT

#include <stdio.h>
#include <string.h>

void getInput(char* input)
{
    printf("[QUASH]: - $:");
	fgets(input, 255, stdin);
    size_t length = strlen(input);
    input[length - 1] = '\0';
    return;
}

#endif