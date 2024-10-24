#ifndef STRSPLIT
#define STRSPLIT

#include <string.h>
#include <stdio.h>
#include <consts.h>

void strSplit(char* input, char* tl[])
{
    char* token;
    int tc = 0;

    char inputToSplit[BSIZE];
    strcpy(inputToSplit, input);
   
    token = strtok(inputToSplit, " \n");
    if(token == NULL)
    {
        tl[0] = NULL;
        return;
    }

    while (token != NULL)
    {
        tl[tc] = strdup(token);  // Make a copy of the token
        tc++;
        token = strtok(NULL, " \n"); 
    }

    for (int i = 0; i < tc; i++) {
        // Check if the token starts with '$'
        if (tl[i][0] == '$') {
            char *variable_name = tl[i] + 1; 
            char *env_value = getenv(variable_name);

            if (env_value != NULL) {
                free(tl[i]);  // Free the old token
                tl[i] = strdup(env_value);  // Make a copy of the environment value
            } else {
                printf("Warning: Environment variable '%s' not found.\n", variable_name);
                q.error = 1;
            }
        }
    }

    if (strcmp(tl[tc - 1], "&") == 0) {
        q.isBackground = 1; 
        free(tl[tc - 1]);  // Free the "&" token
        tl[tc - 1] = NULL; 
    }
    else {
        q.isBackground = 0; 
        tl[tc] = NULL;  // Null terminate the array
    }
}

#endif
