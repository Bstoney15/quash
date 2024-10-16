#ifndef STRSPLIT
#define STRSPLIT

#include <string.h>
#include <stdio.h>
#include <consts.h>

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

    for (int i = 0; i < tc; i++) {
        // Check if the token starts with '$'
        if (tl[i][0] == '$') {
            
            char *variable_name = tl[i] + 1; 

            char *env_value = getenv(variable_name);

            if (env_value != NULL) {

                tl[i] = strdup(env_value);

            } else {
                // If the variable is not found, you might want to handle it
                printf("Warning: Environment variable '%s' not found.\n", variable_name);
                q.error = 1;
            }


        }
    }

    return;
    
}


#endif
