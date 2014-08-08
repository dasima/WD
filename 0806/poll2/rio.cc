#include "rio.h"
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <iostream>
using namespace std;

Rio::Rio(int fd)
    :fd_(fd),
    left_(0),
    bufPtr_(buffer_)
{
}

ssize_t Rio::rio_read(char *usrbuf, size_t n)
{
    size_t nread;
    while(left_ <= 0)
    {
        nread = ::read(fd_, buffer_, sizeof buffer_);
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
    if(left_ < static_cast<int>(n))
        cnt = left_;
    ::memcpy(usrbuf, bufPtr_, cnt);
    left_ -= cnt;
    bufPtr_ += cnt;

    return cnt;
}

ssize_t Rio::rio_readn(char *usrbuf, size_t n)
{
    size_t nleft = n;
    size_t nread;
    char *buf = usrbuf;
    while(nleft > 0)
    {
        if((nread == rio_read(buf, nleft)) == -1)
        {
            return  -1;// 这里不需要EINTR，因为数据已经读取到缓冲区
        }else if(nread == 0)
            break;

        nleft -= nread;
        buf += nread;
    }
    return (n - nleft);
}

ssize_t Rio::rio_readline(char* usrbuf, size_t maxlen)
{
    char *buf = usrbuf;
    size_t nread;
    char c;
    int i;
    for(i = 0; i < static_cast<int>(maxlen - 1); ++i)
    {
        if((nread = rio_read(&c, 1)) == -1)
        {
            return -1;
        }else if(nread == 0)
        {
            if(i == 0)
            {
                return 0;
            }
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

ssize_t Rio::rio_writen(const char *usrbuf, size_t n)
{
    size_t nleft = n;
    size_t nwrite;
    const char *buf = usrbuf;
    while(nleft > 0)
    {
        if((nwrite = ::write(fd_, buf, nleft)) <= 0)
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


