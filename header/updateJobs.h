#ifndef update_Jobs
#define update_Jobs

#include "consts.h"
#include <signal.h>
#include <stdio.h>
#include <sys/wait.h>



void updateJobs() 
{
    for (int i = 0; i < q.jobCount; i++) 
    {
        // Check if the job is still running
        if (kill(q.jList[i].pid, 0) == -1) {
            // Process is no longer running, remove it from the list
            // Shift jobs down in the list

            free(q.jList[i].command);

            for (int j = i; j < q.jobCount - 1; j++) {
                q.jList[j] = q.jList[j + 1];
            }
            q.jobCount--; // Decrement job count
            i--; // Adjust index since we shifted the jobs
        }
    }
}

void sigchld_handler(int signo) {
    // Reap all dead child processes
    while (waitpid(-1, NULL, WNOHANG) > 0);
    updateJobs(); // Call to update jobs list
}

#endif