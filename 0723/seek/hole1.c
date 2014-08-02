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
    int ret = read(fd, buf, 5);
    if(ret == -1)
        ERR_EXIT("read");
    printf("buf ---- %s\n", buf);

    off_t len = lseek(fd, 0, SEEK_CUR);
    printf("len ---- %d\n", (int)len);

    len = lseek(fd, 5, SEEK_CUR);
    printf("len ---- %d\n", (int)len);
    return 0;
}
