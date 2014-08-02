#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>

#define ERR_EXIT(m) \
    do { \
        perror(m);\
        exit(EXIT_FAILURE);\
    }while(0)
static int alarm_fired = 0;
void bing(int sig)
{
    alarm_fired = 1;
}
int main(int argc, const char *argv[])
{
    pid_t pid;
    if((pid = fork()) < 0)
        ERR_EXIT("fork");
    else if(pid == 0)
    {
        sleep(3);
        kill(getppid(), SIGALRM);
        exit(0);
    }else
    {
        printf("parent---waiting bing---\n");
        signal(SIGALRM, bing);
        pause();

        if(alarm_fired)
            printf("ding\n");
        printf("Done\n");
    }

    return 0;
}
