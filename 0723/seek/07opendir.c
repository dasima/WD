#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#define ERR_EXIT(m)\
    do\
    {\
        perror(m);\
        exit(EXIT_FAILURE);\
    }while(0)

int main(int argc, const char *argv[])
{
    int fd1, fd2;
    char buf1[1024] = {0};
    char buf2[1024] = {0};
    fd1 = open("test.txt", O_RDONLY, 0666);
    if(fd1 == -1)
        ERR_EXIT("open error");
    read(fd1, buf1, 5);
    printf("buf1 ---- %s\n", buf1);

    fd2 = open("test.txt", O_RDONLY, 0666);
    if(fd2 == -1)
        ERR_EXIT("open error");
    read(fd2, buf2, 5);
    printf("buf2 ---- %s\n", buf2);

    memset(buf1, 0, sizeof(buf1));
    write(fd1, buf1, 5);
    printf("buf1 --- %s\n", buf1);

    close(fd1);
    close(fd2);
    return 0;
}
