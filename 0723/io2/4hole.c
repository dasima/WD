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
    int fd = open("1.txt", O_WRONLY | O_CREAT | O_TRUNC, 0666);
    if(fd == -1)
        ERR_EXIT("open");
    char buf[] = "hello";
    write(fd, buf, strlen(buf));

    off_t len = lseek(fd, 5, SEEK_CUR);
    printf("offset---- %d\n", (int)len);

    write(fd, "world", strlen("world"));

    close(fd);

    return 0;
}
