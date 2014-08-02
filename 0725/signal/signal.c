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
    printf("ctrl + c\n");
}

int main(int argc, const char *argv[])
{
    sighandler_t old;
    if((old = signal(SIGINT, handler)) == SIG_ERR)
        ERR_EXIT("signal");
    //忽略SIGQUIT， 此时ctrl+‘\'不能起到中断的作用
    if(signal(SIGQUIT, SIG_IGN) == SIG_ERR)
        ERR_EXIT("signal");

    for(;;)
        pause();//暂停程序，直到接收到信号
    return 0;
}
