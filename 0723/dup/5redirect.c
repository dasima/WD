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
int main(int argc, const char *argv[])
{
    int fd = open("test.txt", O_RDONLY, 0666);
    if(fd == -1)
        ERR_EXIT("open");

    //首先关闭STDIN_FILENO,然后将该fd指向test.txt的文件表项
    dup2(fd, STDIN_FILENO);

    char buf[1024];
    fgets(buf, 1024, stdin);
    fputs(buf, stdout);

    close(fd);

    return 0;
}
