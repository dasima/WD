#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <errno.h>
#include <unistd.h>

#define ERR_EXIT(m) \
    do { \
        perror(m);\
        exit(EXIT_FAILURE);\
    }while(0)

typedef void (*sighandler_t)(int);
void handler(int signum)
{
    printf("SIGALRM\n");
}

int main(int argc, const char *argv[])
{
    sighandler_t old;
    if((old = signal(SIGALRM, handler)) == SIG_ERR)
        ERR_EXIT("signal");

    alarm(3);//程序3S后给自己发一个SIGALRM信号

    for(;;)
        pause();
    return 0;

}
