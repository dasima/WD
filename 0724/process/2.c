#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ERR_EXIT(m) \
    do { \
        perror(m);\
        exit(EXIT_FAILURE);\
    }while(0)
/*
 *本例演示父进程、子进程执行顺序
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
        printf("Parent: pid---%d, child---%d\n", getpid(), pid);//此处pid就是子进程的ID

        sleep(3);//这里让子进程先退出
        //否则，父进程先退出会造成子进程成为孤儿进程
        //此时子进程会有进程号为1的系统进程进行释放

    }else
    {
        //子进程
        printf("In child :pid---%d, parent---%d\n", getpid(), getppid());
    }
    return 0;
}
