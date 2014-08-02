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
    pid_t pid = fork();
    if(pid == -1)
        ERR_EXIT("fork");
    else if(pid > 0)
    {
        //sleep(3);//sleep放在printf前是为了让孩子先执行
        printf("parent\n");
        sleep(3);
    }else
    {
        printf("child\n");
    }   
    return 0;
}
