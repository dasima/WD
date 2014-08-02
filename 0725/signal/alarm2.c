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
//alarm与pause协作，可起到sleep的作用
int main(int argc, const char *argv[])
{
    alarm(3);//程序3S后给自己发一个SIGALRM信号

    pause();//暂停程序，等待信号的到来
    return 0;

}
