//Standard libraries
#include <signal.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>

//our libs
#include "../header/getInput.h"
#include "../header/strSplit.h"
#include "../header/consts.h"
#include "../header/commands.h"
#include "../header/countPipes.h"
#include "../header/updateTL.h"
#include "../header/updateJobs.h"

int main(int argc, char* argv[])
{
	system("clear");

	printf("Quash 1.0\n");
	printf("loading\n");

	//set up quash struct
	q.isRunning = 1;
	getcwd(q.cDir, sizeof(q.cDir));
	q.error = 0;
	q.jobCount = 0;

	
	//set up signal handling

	struct sigaction sa;
    sa.sa_handler = sigchld_handler;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = SA_RESTART | SA_NOCLDSTOP;
    sigaction(SIGCHLD, &sa, NULL);


	sleep(1);
	system("clear");

	pid_t pidTracker = -1;

	//pipes
	int fd[2];
	pipe(fd);
	int pipesNeeded;

	// set read pipe as non blocking
	int flags = fcntl(fd[0], F_GETFL, 0);
	flags |= O_NONBLOCK;
	fcntl(fd[0], F_SETFL, flags);


	//read buffers
	char input[BSIZE]; //input buffer
	char* tl[BSIZE]; //token list
	char fromProcess[BSIZE * 10] = "";
	
	while(q.isRunning)
	{
		q.error = 0; //reset error flag
		
		getInput(input);
		strSplit(input, tl);

		// if error is found
		if(q.error == 1)
		{
			continue;
		}

		if(q.isBackground){
			int status;


			pid_t pid = fork();
			if(pid == 0)
			{
				//child
				pidTracker = pid;
			}	
			else
			{
				//parent
				struct job tmp;
				tmp.pid = pid;
				tmp.command = strdup(input);
				strcpy(tmp.status, "running");
				tmp.jobID  = q.jobCount + 1;
				q.jList[q.jobCount] = tmp;
				q.jobCount++;
				continue;
			}
		}

		pipesNeeded = countPipes(tl);
		char** curCommand = updateTL(tl);
		

		for(pipesNeeded; pipesNeeded >= 0; pipesNeeded--)
		{
			if(pipesNeeded > 0)
			{	
				commands(curCommand, fromProcess, fd[1]);
				curCommand = updateTL(tl);
			}
			else
			{
				commands(curCommand, fromProcess, -1);
			}

			read(fd[0], fromProcess, BSIZE*10);
		}

		if(pidTracker == 0)
		{
			exit(0);
		}
		
	}	
	exit(0);	
}

