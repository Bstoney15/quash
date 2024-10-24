#ifndef STRSPLIT
#define STRSPLIT

#include <string.h>
#include <stdio.h>
#include <consts.h>

void strSplit(char* input, char* tl[])
{
    char* token;
    int tc = 0;  // Token counter

    char inputToSplit[BSIZE];
    strcpy(inputToSplit, input);  // Copy input to avoid modifying the original
    
    token = strtok(inputToSplit, " \n");
    if (token == NULL)
    {
        tl[0] = NULL;
        return;
    }

    while (token != NULL)
    {
        tl[tc] = strdup(token);  // Copy the token using strdup
        if (tl[tc] == NULL) {
            q.error = 1;  // Memory allocation failure
            break;
        }
        tc++;
        token = strtok(NULL, " \n");
    }

    // Handle environment variables
    for (int i = 0; i < tc; i++) {
        if (tl[i][0] == '$') {
            char *variable_name = tl[i] + 1;
            char *env_value = getenv(variable_name);
            
            if (env_value != NULL) {
                char* old_token = tl[i];  // Store the pointer before freeing
                free(old_token);  // Free using stored pointer
                
                tl[i] = strdup(env_value);  // Make a copy of the environment value
                
                if (tl[i] == NULL) {
                    q.error = 1;
                    break;
                }
            } else {
                printf("Warning: Environment variable '%s' not found.\n", variable_name);
                q.error = 1;
                break;
            }
        }
    }

    // Handle background process ('&' token)
    if (tc > 0 && strcmp(tl[tc - 1], "&") == 0) {
        q.isBackground = 1;
        free(tl[tc - 1]);  // Free the "&" token
        tl[tc - 1] = NULL;  // Null terminate the array
    } else {
        q.isBackground = 0;
        tl[tc] = NULL;  // Null terminate the array
    }

    // Free allocated memory if an error occurred
    if (q.error == 1) {
        for (int i = 0; i < tc; i++) {
            free(tl[i]);
        }
    }
}

#endif
