#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ERR_EXIT(m) \
    do { \
        perror(m);\
        exit(EXIT_FAILURE);\
    }while(0)
/*
 *本例演示孤儿进程
 */
int main(int argc, const char *argv[])
{
    pid_t pid;
    pid = fork();
    if(pid == -1)
        ERR_EXIT("fork");
    else if(pid > 0)
    {
        //父进程
        printf("In parent : pid---%d, child---%d\n", getpid(), pid);
        exit(EXIT_FAILURE);
    }else
    {
        sleep(1);
        //子进程
        printf("In child: pid---%d, parent---%d\n", getpid(), getppid());
        sleep(3);
    }

    
    return 0;
}
