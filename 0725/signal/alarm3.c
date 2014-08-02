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
//SIGALRM信号
void handler(int signum)
{
    static int beeps = 0;
    printf("beep\n");
    if(++beeps < 5)//为什么if也能一直输出？？？
        alarm(1);
    else
    {
        printf("boom\n");
        exit(EXIT_SUCCESS);
    }
}

int main(int argc, const char *argv[])
{
    sighandler_t old;
    if((old = signal(SIGALRM, handler)) == SIG_ERR)
        ERR_EXIT("signal");

    alarm(3);//程序3S后给自己发一个SIGALRM信号

    while(1)
        ;
    return 0;

}
