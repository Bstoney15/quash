#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char* argv[])
{
	system("clear");

	printf("Quash 1.0\n");
	printf("loading\n");
	
	//set up signal handling

	sleep(3);

	system("clear");

	int BSIZE = 100;
	char input[BSIZE];
	
	while(input != "exit")
	{
		printf("QUASH: $");
		scanf("%s", input);
	}	


	exit(0);	
}

