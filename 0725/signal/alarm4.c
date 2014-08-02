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
#define N 10
typedef void (*sighandler_t)(int);
//处理SIGCHLD，防止僵尸进程
void handler(int signum)
{
    pid_t pid;
    if((pid = waitpid(-1, NULL, 0)) < 0)
        ERR_EXIT("waitpid");
    printf("handler process child %d\n", pid);
    sleep(2);//故意去阻塞别的SIGCHLD信号
}

int main(int argc, const char *argv[])
{
    if(( signal(SIGCHLD, handler)) == SIG_ERR)
        ERR_EXIT("signal");

    pid_t pid;
    int i;
    for(i = 0; i < N; ++i)
    {
        if((pid = fork()) < 0)
            ERR_EXIT("fork");
        else if(pid == 0)
        {
            printf("hello from child %d\n", getpid());
            sleep(2);
            exit(EXIT_SUCCESS);
        }
    }

    int n;
    char buf[1024];
    //这里将发生阻塞
    if((n = read(STDIN_FILENO, buf, 1024)) < 0)
        ERR_EXIT("read error");
    printf("parent process input\n");

    while(1)
        ;

    return 0;

}
