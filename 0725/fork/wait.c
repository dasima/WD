#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#define ERR_EXIT(m) \
    do { \
        perror(m);\
        exit(EXIT_FAILURE);\
    }while(0)
int main(int argc, const char *argv[])
{
    pid_t pid;
    char *message;
    int n;
    int exit_code ;

    printf("fork start\n");
    pid = fork();
    switch(pid)
    {
        case -1 :
            perror("fork failed");
            exit(1);
        case 0 :
            message = "child";
            n = 5;
            exit_code = 37;
            break;
        default :
            message = "parent";
            n = 3;
            exit_code = 0;
            break;

    }
    for(; n > 0; --n)
    {
        puts(message);
        sleep(1);
    }
    
    int stat;
    if(pid < 0)
        ERR_EXIT("fork");
    else if(pid > 0)
    {
        pid_t child_pid;
        child_pid = wait(&stat);
        printf("Child has finished: pid --- %d\n", child_pid);
        if(WIFEXITED(stat))//子程序正常结束
            printf("Child exited with code : %d\n", WEXITSTATUS(stat));//返回子进程退出码
        else
            printf("Child terminated abnormally\n");
        exit(exit_code);
    }

    return 0;
}
