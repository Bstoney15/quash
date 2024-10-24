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
        tl[tc] = strdup(token);  
        tc++;
        token = strtok(NULL, " \n"); 
    }

    for (int i = 0; i < tc; i++) {
        if (tl[i][0] == '$') {
            char *variable_name = tl[i] + 1; 
            char *env_value = getenv(variable_name);

            if (env_value != NULL) {
                free(tl[i]);  
                tl[i] = strdup(env_value); 
            } else {
                printf("Warning: Environment variable '%s' not found.\n", variable_name);
                q.error = 1;
            }
        }
    }

    if (strcmp(tl[tc - 1], "&") == 0) {
        q.isBackground = 1; 
        free(tl[tc - 1]);  
        tl[tc - 1] = NULL; 
    }
    else {
        q.isBackground = 0; 
        tl[tc] = NULL;  
    }
}

#endif
