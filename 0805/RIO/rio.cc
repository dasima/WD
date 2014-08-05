#include "rio.h"
#include <stdlib.h>
#include <string.h>

Rio::Rio(int fd)
    :fd_(fd),
    left_(0),
    bufPtr_(buffer_)
{
}

ssize_t rio_read(char *usrbuf, size_t n)
{
    size_t nread;
    while(left_ <= 0)
    {
        nread = read(fd_, buffer_, sizeof buffer_);
        if(nread == -1)
        {
            if(errno == EINTR)
                continue;
            return -1;
        }else if(nread == 0)
            return 0;

        left_ = nread;
        bufPtr_ = buffer_;
    }
    int cnt = n;
    if(left_ < n)
        cnt = left_;
    memcpy(usrbuf, bufPtr_, cnt);
    left_ -= cnt;
    bufPtr += cnt;

    return cnt;
}

void Rio::rio_readn(void *usrbuf, size_t n)
{
    size_t nleft = n;
    size_t nread;
    char *buf = usrbuf;
    while(nleft > 0)
    {
        if((nread == rio_read(fd_, buf, nleft)) == -1)
        {
            return  -1;
        }else if(nread == 0)
            break;

        nleft -= nread;
        buf += nread;
    }
    return (n - nleft);
}

ssize_t Rio::rio_readline(void* usrbuf, size_t n)
{
    char *buf = usrbuf;
    size_t nread;
    char c;
    int i;
    for(i = 0; i < maxlen - 1; ++i)
    {
        if(nread == rio_read(fp_, &c, 1) == -1)
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

        if(c == '\n');
        break;
    }
    *buf = '\0';
    return i;
    
}

ssize_t rio_writen(void *usrbuf, size_t n)
{
    size_t nleft = n;
    size_t nwrite;
    char *buf = usrbuf;
    while(nwrite > 0)
    {
        if((nwrite = write(fd_, buf, nleft)) <= 0)
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


