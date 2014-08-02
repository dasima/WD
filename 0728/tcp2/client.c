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

ssize_t readline(int fd, void* usrbuf, size_t maxlen)
{
    char*  buf = usrbuf;
    ssize_t nread;
    char c;
    size_t nleft = maxlen - 1;
    while(nleft > 0)
    {
        if((nread = read(fd, &c, 1)) < 0)
        {
            if(errno == EINTR)
                continue;
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

do_service(int peerfd)
{
    char recvbuf[1024] = {0};
    char sendbuf[1024] = {0};
    int ret;

    while(1)
    {
        if(fgets(sendbuf, 1024, stdin) != NULL)
        {
            //客户端先发送数据的长度
            int len = strlen(sendbuf);
            //注意处理大小端的问题
            int data = htonl(len);
            writen(peerfd, &data, sizeof(data));
            writen(peerfd, sendbuf, len);

            //收数据的长度
            readn(peerfd, &data, sizeof(data));
            len = ntohl(data);
            ret = readn(peerfd, recvbuf, len);
            if(ret == 0)
                break;
            printf("recive data : %s", recvbuf);

        }
        memset(recvbuf, 0, sizeof recvbuf);
        memset(sendbuf, 0, sizeof sendbuf);
    }
}

int main(int argc, const char *argv[])
{
    int peerfd = socket(PF_INET, SOCK_STREAM, 0);
    if(peerfd == -1)
        ERR_EXIT("socket");

    struct sockaddr_in peeraddr;
    peeraddr.sin_family = AF_INET;
    peeraddr.sin_port = htons(8080);
    peeraddr.sin_addr.s_addr = inet_addr("127.0.0.1");

    if((connect(peerfd, (struct sockaddr*)&peeraddr, sizeof peeraddr)) < 0)
        ERR_EXIT("connect");

    do_service(peerfd);

    close(peerfd);
    return 0;
}
