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
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#define ERR_EXIT(m) \
    do { \
        perror(m);\
        exit(EXIT_FAILURE);\
    }while(0)

/*
 *TCP存在一个粘包问题（初步解决）
 *处理方式是：在每条报文前加上要发送的字节数，
 *（这个字节数要转化成网络序）
 *然后用writen函数写入相应字节
 *接收方只需要先读取前面的字节数获取消息的长度n
 *然后使用readn函数接受即可
 *
 */
ssize_t readn(int fd, void *usrbuf, size_t n)
{
    size_t nleft = n;
    ssize_t nread ;
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
    size_t nleft = n;
    ssize_t nwrite;
    char *buf = usrbuf;
    while(nleft > 0)
    {
        if((nwrite = write(fd, buf, nleft)) <= 0)
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

ssize_t readline(int fd, void *usrbuf, size_t maxlen)
{
    char* buf = usrbuf;
    ssize_t nread;
    size_t nleft = maxlen - 1;
    char c;
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
    return (maxlen - nleft -1);
}

void do_service(int peerfd)
{
    char recvbuf[1042] = {0};
    int ret;
    while(1)
    {
        memset(recvbuf, 0, sizeof recvbuf);
        int data;
        int len;
        readn(peerfd, &data, sizeof(data));
        len = ntohl(data);
        ret = readn(peerfd, recvbuf, len);
        if(ret == -1)
        {
            return ;
        }else if(ret == 0 )
            break;
        else
        {
            writen(peerfd, &data, sizeof(data));
            writen(peerfd, recvbuf, len);
        }

    }
}


int main(int argc, const char *argv[])
{
    int listenfd = socket(AF_INET, SOCK_STREAM, 0);
    if(listenfd == -1)
        ERR_EXIT("socket");

    int on = 1000;
    if((setsockopt(listenfd, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on))) < 0)
        ERR_EXIT("setsockopt");

    struct sockaddr_in serveraddr;
    serveraddr.sin_family = AF_INET;
    serveraddr.sin_port = htons(8080);
    serveraddr.sin_addr.s_addr = htonl(INADDR_ANY);

    if((bind(listenfd, (struct sockaddr*)&serveraddr, sizeof serveraddr)) < 0)
        ERR_EXIT("bind");

    if(listen(listenfd, SOMAXCONN) < 0)
        ERR_EXIT("listen");

    int peerfd;
    if((peerfd = accept(listenfd, NULL, NULL)) < 0)
        ERR_EXIT("accept");

    do_service(peerfd);

    close(peerfd);
    close(listenfd);
    return 0;
}
