#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define ERR_EXIT(m) \
    do { \
        perror(m);\
        exit(EXIT_FAILURE);\
    }while(0)

int main(int argc, const char *argv[])
{
    pid_t pid;
    if((pid = fork()) < 0)
        ERR_EXIT("fork");
    else if(pid == 0)
        execlp("ls", "ls", "-l", NULL);
    else
        sleep(3);
    return 0;
}
