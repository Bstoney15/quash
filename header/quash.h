#ifndef QUASH
#define QUASH


struct job {
    int jobID; 
    pid_t pid; 
    char* command;
    char status[25]; 
};

struct quash
{
    int isRunning;
    char cDir[255];
    int error;
    int isBackground; 
    struct job jList[255];
    int jobCount; 
};

#endif