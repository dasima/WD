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
    int fd = open("test.txt", O_RDONLY);
    if(fd == -1)
        ERR_EXIT("open");

    pid_t pid;
    if((pid = fork()) < 0)
        ERR_EXIT("fork");
    else if(pid == 0)
    {
        char buf[100] = {0};
        read(fd, buf, 3);
        printf("in child buf--- %s\n", buf);
        close(fd);        
    }else
    {
        sleep(3);
        char buf[10] = {0};
        read(fd, buf, 3);
        printf("in parent buf--- %s\n", buf);
        close(fd);
    }
    return 0;
}
