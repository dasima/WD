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
    size_t nleft = n;//表示还要读取的字节数
    ssize_t nread;
    char* buf = usrbuf;//控制read函数存放的位置

    while(nleft > 0)
    {
        if((nread = read(fd, buf, nleft)) == -1)
        {
            if(errno == EINTR)
                continue;//中断，则再次读取
            return -1;//ERROR
        }else if(nread == 0)//EOF
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
        nwrite == 0;//也属于错误
        if((nwrite = write(fd, buf, nleft)) == -1)
        {
            if(errno == EINTR)
                continue;
            return -1;//-1和0
        }else if(nwrite == 0)
            break;

        nleft -= nwrite;
        buf += nwrite;
    }
    return n;
}

//recv_peek完成依次正确的读取过程
ssize_t recv_peek(int sockfd, void* buf, size_t len)
{
    int nread;
    while(1)
    {
        //这个过程只调用一次
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
    int nread;//一次IO读取的数量
    int nleft = maxline;//还剩余的字节数
    char *ptr = usrbuf;//存放数据的指针位置
    int ret;//readn的返回值
    int total = 0;//目前总共读取的字节数
    while(nleft > 0)
    {
        //这一次调用只是预览数据，并没有把数据从缓冲区取走
        ret = recv_peek(fd, ptr, nleft);
        //这里的字节不够不是错误
        if(ret <= 0)
            return ret;

        nread = ret;
        int i;
        for(i = 0; i < nread; ++i)
        {
            if(ptr[i] == '\n')
            {
                //遇到换行了，这里才是真正的读取过程
                ret = readn(fd, ptr, i+1);
                if(ret != i+1)
                    return -1;
                total += ret;
                //返回此行的长度'\n'也包含其中
                return total;
            }
        }

        //如果没有找到\n，就把这些数据全部接受
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
