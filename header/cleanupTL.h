#ifndef CLEANUPTL
#define CLEANUPTL

void cleanUpTL(char** tl)
{
    if (tl == NULL) return;
    for(int i = 0; tl[i] != NULL; i++) {
        free(tl[i]);
    }
}


#endif