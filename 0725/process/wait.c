#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
        exit(EXIT_SUCCESS);
    else
    {
        int ret = wait(NULL);
        //这里返回的是儿子进程ID
        printf("child --- %d\n", ret);
        while(1)
            ;
    }
    return 0;
}
