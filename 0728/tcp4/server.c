#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <errno.h>

#define ERR_EXIT(m) \
    do { \
        perror(m);\
        exit(EXIT_FAILURE);\
    }while(0)

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
                continue;
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
    char* buf = usrbuf;
    ssize_t nwrite;
    size_t nleft = n;

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
    int nleft = maxline;
    char *ptr = usrbuf;
    int ret;
    int total = 0;
    while(nleft > 0)
    {
        ret = recv_peek(fd, ptr, nleft);
        if(ret <= 0)
            return ret;

        nread = ret;
        int i;
        for(i = 0; i < nread; ++i)
        {
            if(ptr[i] == '\n')
            {
                ret = readn(fd, ptr, i+1);
                if(ret != i+1)
                    return -1;
                total += ret;
                return total;
            }
        }
        ret = readn(fd, ptr, nread);
        if(ret != nread)
            return -1;
        nleft -= nread;
        total += nread;
        ptr += nread;
    }
    return maxline;
}

do_service(int peerfd)
{
    char recvbuf[1024] = {0};
    int ret;
    while(1)
    {
        ret = readline(peerfd, recvbuf, 1024);
        if(ret == 0)
            break;
        writen(peerfd, recvbuf, strlen(recvbuf));
        memset(recvbuf, 0, sizeof recvbuf);
    }
}

int main(int argc, const char *argv[])
{
    int listenfd = socket(PF_INET, SOCK_STREAM, 0);
    if(listenfd == -1)
        ERR_EXIT("socket");

    struct sockaddr_in sockaddr;
    sockaddr.sin_family = AF_INET;
    sockaddr.sin_port = htons(8080);
    sockaddr.sin_addr.s_addr = inet_addr("127.0.0.1");

    if(bind(listenfd, (struct sockaddr*)&sockaddr, sizeof(sockaddr)) < 0)
        ERR_EXIT("bind");

    if(listen(listenfd, SOMAXCONN) < 0)
        ERR_EXIT("listen");

    int peerfd;
    if((peerfd = accept(listenfd, NULL, NULL)) < 0)
        ERR_EXIT("accept");

    do_service(peerfd);

    close(peerfd);
    return 0;
}
