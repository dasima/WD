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
void set_flag(int fd, int flags);
void clr_flag(int fd, int flags);

int main(int argc, const char *argv[])
{
    char buf[1024] = {0};
    int ret;
    set_flag(0, O_NONBLOCK);
    clr_flag(0, O_NONBLOCK);
    ret = read(0, buf, 1024);
    if(ret == -1)
        ERR_EXIT("read fail");

    printf("buf ---- %s\n", buf);
    return 0;
}

void set_flag(int fd, int flags)
{
    int val;
    val = fcntl(fd, F_GETFL, 0);
    if(val == -1)
        ERR_EXIT("fcntl ");

    val |= flags;
    if(fcntl(fd, F_SETFL, val) < 0)
        ERR_EXIT("fcntl");
}

void clr_flag(int fd, int flags)
{
    int val;
    val = fcntl(fd, F_GETFL, 0);
    if(val == -1)
        ERR_EXIT("fcntl");
    val &= ~flags;
    if(fcntl(fd, F_SETFL, 0) < 0)
        ERR_EXIT("fcntl");
}
