#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#define ERR_EXIT(m) \
    do { \
        perror(m);\
        exit(EXIT_FAILURE);\
    }while(0)
/*
 *通过write的执行结果查看父进程、子进程的执行顺序
 *
 */
int main(int argc, const char *argv[])
{
    //以写的方式打开，文件不存在就创建，存在则清空后写入
    int fd = open("test.txt", O_WRONLY | O_CREAT | O_TRUNC, 0666);
    if(fd == -1)
        ERR_EXIT("open");

    pid_t pid = fork();
    if(pid == -1)
        ERR_EXIT("fork");
    else if(pid > 0)
    {
        sleep(10);
        write(fd, "hello", strlen("hello"));
        sleep(3);
        close(fd);
    }else
    {
        write(fd, "world", strlen("world"));
        close(fd);
    }

    return 0;
}
