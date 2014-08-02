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

    char buf[1024] = {0};
    read(fd, buf, 5);
    printf("buf --- %s\n", buf);

    memset(buf, 0, sizeof(buf));
    int fd2;
    dup2(fd, fd2);
    read(fd2, buf, 5);
    printf("buf --- %s\n", buf);
    close(fd);
    close(fd2);
    return 0;
}
