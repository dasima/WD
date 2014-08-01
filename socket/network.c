#include "network.h"
ssize_t readn(int fd, void* usrbuf, size_t n)
{
    size_t nleft = n;
    ssize_t nread;
    char* buf = usrbuf;

    while(nleft > 0)
    {
        if((nread = read(fd, buf, nleft)) == -1)
        {
            if(errno == EINTR)
                nread = 0;
            return -1;
        }else if(nread == 0)
            break;

        nleft -= nread;
        buf += nread;
    }
    return (n - nleft);
}

ssize_t writen(int fd, void* usrbuf, size_t n)
{
    char *buf = usrbuf;
    size_t nleft = n;
    ssize_t nwrite;

    while(nleft > 0)
    {
        if((nwrite = write(fd, buf, nleft)) == -1)
        {
            if(errno == EINTR)
                continue;
            return -1;

        }else if(nwrite == 0)
            break;

        nleft -= nwrite;
        buf += nwrite;
    }
    return n;
}

ssize_t recv_peek(int sockfd, void* buf, size_t len)
{
    int nread;
    while(1)
    {
        nread = recv(sockfd, buf, len, MSG_PEEK);
        if(nread < 0 && errno == EINTR)
            continue;
        if(nread < 0)
            return -1;
        break;
    }
    return nread;
}

ssize_t readline(int fd, void* usrbuf, size_t maxline)
{
    int nread;
    int nleft = maxline - 1;
    char* buf = usrbuf;
    int ret;
    int total = 0;

    while(nleft > 0)
    {
        ret = recv_peek(fd, buf, nleft);
        if(ret <= 0)
            return ret;
        nread = ret;
        int i;
        for(i = 0; i < nread; ++i)
        {
            if(buf[i] == '\n')
            {
                ret = readn(fd, buf, i+1);
                if(ret != i+1)
                    return -1;
                total += ret;
                buf += ret;
                *buf = 0;
                return total;
            }
        }
        ret = readn(fd, buf, nread);
        if(ret != nread)
            return -1;
        nleft -= nread;
        total += nread;
        buf += nread;//指针后移
    }
    *buf = 0;
    return maxline;
}

