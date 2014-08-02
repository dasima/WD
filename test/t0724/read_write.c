#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <fcntl.h>

#define ERR_EXIT(m) \
    do { \
        perror(m);\
        exit(EXIT_FAILURE);\
    }while(0)

ssize_t writen(int fd, void* usrbuf, size_t n);
ssize_t readn(int fd, void *usrbuf, size_t n);
ssize_t readline(int fd, char* usrbuf, size_t maxlen);
int main(int argc, const char *argv[])
{
    int fd = open("test.txt", O_RDONLY);
    if(fd == -1)
        ERR_EXIT("open");

    int ret;
    char buf[1024] = {0};
    while((ret = readn(fd, buf, 10)) > 0)
        writen(STDOUT_FILENO, buf, ret);

    ret = 0;
    while((ret = readline(STDIN_FILENO, buf, 5)) )
        printf("ret --- %d, buf --- %s\n", ret, buf);
    
    return 0;
}

ssize_t readn(int fd, void *usrbuf, size_t n)
{
    size_t nleft = n;
    char* buf = usrbuf;
    size_t nread;
    while(nleft > 0)
    {
        if((nread = read(fd, buf, nleft)) == -1)
        {
            if(nread == EINTR)
                nread = 0;
            else
                return -1;
        }else if(nread == 0)
        {
            break;
        }

        nleft -= nread;
        buf += nread;
    }
    return (n - nleft);
}

ssize_t writen(int fd, void* usrbuf, size_t n)
{
    size_t nleft = n;
    char* buf = usrbuf;
    size_t nwrite;
    while(nleft > 0)
    {
        if((nwrite = write(fd, buf, nleft)) <= 0)
        {
            if(nwrite == EINTR)
                nwrite = 0;
            else
                return -1;
        }

        nleft -= nwrite;
        buf += nwrite;
    }
    return n;
}

ssize_t readline(int fd, char* usrbuf, size_t maxlen)
{
    size_t nleft = maxlen - 1;
    char c;
    char* buf = usrbuf;
    size_t nread;
    while(nleft >= 0)
    {
        if((nread = read(fd, &c, 1)) == -1)
        {
            if(errno == EINTR)
                continue;
            else
                return -1;
        }else if(nread == 0)
            break;

        *buf = c;
        ++buf;
        --nleft;

        if(c == '\n')
            break;
    }
    *buf = '\0';
    return (maxlen - nleft - 1);
}

















