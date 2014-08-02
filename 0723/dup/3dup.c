#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <errno.h>
#include <signal.h>
#define ERR_EXIT(m)\
    do\
    {\
        perror(m);\
        exit(EXIT_FAILURE);\
    }while(0)

//????NO
int main(int argc, const char *argv[])
{
    int fd = open("test.txt", O_RDONLY, 0666);
    if(fd == -1)
        ERR_EXIT("open");

    int fd2 = 5;
    //dup2可以手工指定复制后的fd
    //如果该fd已经被占用，那么先关闭
    dup2(fd, fd2);

    char buf[100] = {0};
    read(fd2, buf, 10);
    printf("buf --- %s\n", buf);

    close(fd);
    close(fd2);

    return 0;
}
