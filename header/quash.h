#ifndef QUASH
#define QUASH


struct job {
    int jobID; 
    pid_t pid; 
    char* command;
    char* status; 
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