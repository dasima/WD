#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/*
 *本例子演示获取进程ID、父进程ID等
 *
 */
int main(int argc, const char *argv[])
{
    //获取进程ID
    printf("pid---%d\n", getpid());
    //获取父进程ID
    printf("ppid-- -%d\n", getppid());
    //获取用户ID
    printf("uid---%d\n", getuid());
    //获取有效用户ID
    printf("euid---%d\n", geteuid());
    return 0;
}
