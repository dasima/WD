#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#define ERR_EXIT(m) \
    do { \
        perror(m);\
        exit(EXIT_FAILURE);\
    }while(0)
/*
 *通过read的执行结果查看父进程、子进程执行顺序
 */
int main(int argc, const char *argv[])
{
    int fd = open("test.txt", O_RDONLY);
    if(fd == -1)
        ERR_EXIT("open");

    pid_t pid;
    pid = fork();
    if(pid == -1)
        ERR_EXIT("fork");
    else if(pid > 0)
    {
        //让子进程先执行
        sleep(3);
        char buf[1024] = {0};
        read(fd, buf, 3);
        printf("In parent: buf---%s\n", buf);
        sleep(3);
    }else
    {
        char buf[1024] = {0};
        read(fd, buf, 3);//read读取后指针后移
        printf("In child: buf---%s\n",buf);
    }
    
    return 0;
}
