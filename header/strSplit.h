#ifndef STRSPLIT
#define STRSPLIT

#include <string.h>
#include <stdio.h>
#include <consts.h>
#include <ctype.h>

void strSplit(char* input, char* tl[])
{
    char* token;
    int tc = 0;  // Token counter

    char inputToSplit[BSIZE];
    strcpy(inputToSplit, input);  
    
    token = strtok(inputToSplit, " \n");
    if (token == NULL)
    {
        tl[0] = NULL;
        return;
    }

    while (token != NULL)
    {
        tl[tc] = strdup(token);  
        if (tl[tc] == NULL) {
            q.error = 1;  // Memory allocation failure
            break;
        }
        tc++;
        token = strtok(NULL, " \n");
    }

    // Handle environment variables
for (int i = 0; i < tc; i++) {
    char *token = tl[i];
    char *dollar_sign = strchr(token, '$');  // Find the first occurrence of $

    while (dollar_sign != NULL) {
        char *variable_name = dollar_sign + 1;
        char *end = variable_name;

        // Find the end of the variable name
        while (*end && (isalnum(*end) || *end == '_')) {
            end++;
        }

        size_t var_len = end - variable_name;
        char var_name[var_len + 1];
        strncpy(var_name, variable_name, var_len);
        var_name[var_len] = '\0';

        char *env_value = getenv(var_name);
        if (env_value != NULL) {
            // Calculate new token length
            size_t prefix_len = dollar_sign - token;
            size_t env_len = strlen(env_value);
            size_t suffix_len = strlen(end);
            size_t new_len = prefix_len + env_len + suffix_len + 1;

            char *new_token = malloc(new_len);
            if (new_token == NULL) {
                q.error = 1;
                break;
            }

            // Construct the new token
            strncpy(new_token, token, prefix_len);
            strcpy(new_token + prefix_len, env_value);
            strcpy(new_token + prefix_len + env_len, end);

            free(tl[i]);
            tl[i] = new_token;

            // Update token pointer
            token = tl[i];
        } else {
            printf("Warning: Environment variable '%s' not found.\n", var_name);
            q.error = 1;
            break;
        }

        // Search for the next occurrence of $
        dollar_sign = strchr(token, '$');
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
