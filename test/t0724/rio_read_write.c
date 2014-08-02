#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>

#define ERR_EXIT(m) \
    do { \
        perror(m);\
        exit(EXIT_FAILURE);\
    }while(0)

#define RIO_BUFFER 8192
typedef struct
{
    int fd_;
    int left_;
    char* bufPtr_;
    char buffer_[RIO_BUFFER];
}Rio_t;
int main(int argc, const char *argv[])
{

    
    return 0;
}

void rio_init(Rio_t *rp, int fd)
{
    rp -> fd_ = fd;
    rp -> left_ = 0;
    rp -> bufPtr_ = rp -> buffer_;
}

ssize_t rio_read(Rio_t *rp, char *usrbuf, size_t n)
{
    size_t nread;
    while(rp -> left_ <= 0)
    {
        nread = read(rp -> fd_, rp -> buffer_, sizeof(rp -> buffer_));
        if(nread == -1)
        {
            if(nread == -1)
                continue;
            else
                return -1;
        }else if(nread == 0)
            break;

        rp -> left_ = nread;
        rp -> bufPtr_ = rp -> buffer_;
    }

    int cnt;
    if(rp -> left_ < n)
        cnt = rp -> left_;
    memcpy(usrbuf, rp -> bufPtr_, cnt);
    rp -> left_ -= cnt;
    rp -> bufPtr_ += cnt;

    return cnt;
}

ssize_t rio_readn(Rio_t *rp, void *usrbuf, size_t n)
{
    size_t nleft = n;
    size_t nread;
    char* buf = usrbuf;
    while(nleft > 0)
    {
        if((nread = rio_read(rp, buf, nleft)) == -1)
        {
            return -1;
        }else if(nread == 0)
            break;

        nleft -= nread;
        buf += nread;
    }
    return (n - nleft);
}

ssize_t rio_writen(int fd, void *usrbuf, size_t n)
{
    size_t nleft = n;
    size_t nwrite;
    char *buf = usrbuf;
    while(nleft > 0)
    {
        nwrite = write(fd, buf, nleft);
        if(nwrite <= 0)
        {
            if(errno == EINTR)
                nwrite = 0;
            return -1;
        }
        nleft -= nwrite;
        buf += nwrite;
    }
    return n;
}

ssize_t rio_readline(Rio_t *rp, void *usrbuf, size_t maxlen)
{
    size_t nread;
    char *buf = usrbuf;
    char c;
    int i;
    for(i = 0; i < maxlen - 1; ++i)
    {
        if((nread = rio_read(rp, &c, 1)) == -1)
        {
            return -1;
        }else if(nread == 0)
        {
            if(i == 0)
                return 0;
            break;
        }

        *buf = c;
        ++buf;

        if(c == '\n')
            break;
    }
    *buf = '\0';
    return i;
}














