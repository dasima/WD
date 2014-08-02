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
int main(int argc, const char *argv[])
{
    char buf[100] = {0};
    int fd = open("1.txt", O_RDONLY);
    if(fd == -1)
        ERR_EXIT("open");

    while(read(fd, buf, 5))
    {
        write(STDOUT_FILENO, buf, 5);
        printf("\n");
        printf("------------\n");
    }
    return 0;
}
