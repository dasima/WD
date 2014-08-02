#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <errno.h>
#include <poll.h>

#define ERR_EXIT(m)\
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

ssize_t recv_peek(int fd, void* buf, size_t len)
{
    int nread;
    while(1)
    {
        //把recv的第四个参数设置为MSG_PEEK
        //在调用recv的时候，数据读到缓冲中去，
        //但是缓冲区并不擦除数据
        nread = recv(fd, buf, len, MSG_PEEK);
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
    char*  buf = usrbuf;
    ssize_t nread;
    size_t nleft = maxline;
    int ret;
    int total = 0;
    while(nleft > 0)
    {
        //把数据读到缓冲区中
        ret = recv_peek(fd, buf, nleft);
        if(ret <= 0)
            return ret;

        nread = ret;
        int i;
        //i从1到nread开始遍历，知道读到换行为止
        for(i = 0; i < nread; ++i)
        {
            //如果buf[i]为换行，则读取i+1个字符，
            //return，读取一行成功
            if(buf[i] == '\n')
            {
                ret = readn(fd, buf, i+1);
                if(ret != i+1)
                    return -1;
                total += ret;
                return total;
            }
        }

        //如果for循环后运行到这里，说明没遇到换行
        //读取readn字节的数据
        ret = readn(fd, buf, nread);
        if(ret != nread)
            return -1;

        nleft -= nread;
        total += nread;
        buf += nread;
    }
    return maxline;
}

void do_service(int peerfd)
{
    char recvbuf[1024] = {0};
    char sendbuf[1024] = {0};
    memset(recvbuf, 0x00, sizeof(recvbuf));
    memset(sendbuf, 0x00, sizeof(sendbuf));

    //准备工作
    struct pollfd client[2];//监听2个fd文件描述符
    client[0].fd = fileno(stdin);
    client[0].events = POLLIN;//表示监听读事件
    client[1].fd = peerfd;
    client[1].events = POLLIN;

    int maxi = 1;//数组最大可用下标
    int nread;//接收poll返回值

    while(1)
    {
        //int poll(struct pollfd *fds, nfds_t nfds, int timeout);
        //-1表示永久等待
        nread = poll(client, maxi + 1, -1);
        if(nread == -1)
        {
            if(errno == EINTR)
                continue;
            ERR_EXIT("poll");
        }else if(nread == 0)
            continue;

        //依次检查stdin和peerfd
        if(client[0].revents & POLLIN)//client[0]的返回状态中含有POLLIN
        {
            if(fgets(sendbuf, 1024, stdin) == NULL)
            {
                shutdown(peerfd, SHUT_WR);
                client[0].fd = -1;//停止监听stdin
            }else
            {
                writen(peerfd, sendbuf, strlen(sendbuf));
                memset(sendbuf, 0x00, sizeof(sendbuf));
            }
        }
        if(client[1].revents & POLLIN)
        {
            int ret = readline(peerfd, recvbuf, 1024);
            if(ret == -1)
                ERR_EXIT("readline");
            else if(ret == 0)
            {
                printf("server close\n");
                close(peerfd);
                exit(-1);
            }else
            {
                printf("recv data :%s", recvbuf);
                memset(recvbuf, 0x00, sizeof(recvbuf));
            }   
        }
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
