//Standard libraries
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

//our libs
#include "../header/getInput.h"
#include "../header/strSplit.h"
#include "../header/consts.h"
#include "../header/commands.h"

int main(int argc, char* argv[])
{
	system("clear");

	printf("Quash 1.0\n");
	printf("loading\n");

	//set up quash struct
	q.isRunning = 1;
	q.cDir = getenv("HOME");

	
	//set up signal handling

	sleep(1);

	system("clear");

	char input[BSIZE]; //input buffer
	char* tl[BSIZE]; //token list
	
	while(q.isRunning)
	{
		getInput(input);
		strSplit(input, tl);
		commands(tl);

	
	}	


	exit(0);	
}

