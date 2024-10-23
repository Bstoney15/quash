//Standard libraries
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

int main(int argc, char* argv[])
{
	system("clear");

	printf("Quash 1.0\n");
	printf("loading\n");

	//set up quash struct
	q.isRunning = 1;
	getcwd(q.cDir, sizeof(q.cDir));
	q.error = 0;

	
	//set up signal handling

	sleep(1);

	system("clear");

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


	
	}	
	exit(0);	
}

