#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define ERR_EXIT(m) \
    do { \
        perror(m);\
        exit(EXIT_FAILURE);\
    }while(0)

/*
 *利用fork产生的父子进程
 *地址空间是独立的
 */
int g_val = 9;
int main(int argc, const char *argv[])
{
    pid_t pid;
    pid = fork();
    if(pid == -1)
        ERR_EXIT("fork");
    else if(pid > 0)
    {
        sleep(3);
        printf("In parent: val---%d\n", g_val);//9
        sleep(3);
    }else
    {
        ++g_val;
        printf("In child : val---%d\n", g_val);//10
    }
    return 0;
}
