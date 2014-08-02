#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define ERR_EXIT(m) \
    do { \
        perror(m);\
        exit(EXIT_FAILURE);\
    }while(0)

/*
 *与fork相比较
 *vfork在产生子进程的时候，没有复制地址空间，而是与父进程共享
 */
int g_val = 9;
int main(int argc, const char *argv[])
{
    pid_t pid = vfork();
    if(pid == -1)
        ERR_EXIT("fork");
    else if(pid > 0)
    {
        sleep(3);
        printf("In parent: val---%d\n", g_val);//10
        sleep(3);
    }else
    {
        ++g_val;
        printf("In child: val---%d\n", g_val);//10
        exit(EXIT_FAILURE);
    }
    
    return 0;
}
