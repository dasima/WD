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
#include <sys/epoll.h>

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

do_service(int peerfd)
{
    char recvbuf[1024] = {0};
    char sendbuf[1024] = {0};
    memset(recvbuf, 0x00, sizeof(recvbuf));
    memset(sendbuf, 0x00, sizeof(sendbuf));

    //准备工作
    //创建epoll句柄，epollfd
    int epollfd = epoll_create(2);
    if(epollfd == -1)
        ERR_EXIT("epoll_create");

    //注册两个fd
    struct epoll_event ev;
    ev.events = EPOLLIN;
    ev.data.fd = STDIN_FILENO;
    if(epoll_ctl(epollfd, EPOLL_CTL_ADD, STDIN_FILENO, &ev) == -1)
        ERR_EXIT("epoll_ctl");
    ev.events = EPOLLIN;
    ev.data.fd = peerfd;
    if(epoll_ctl(epollfd, EPOLL_CTL_ADD, peerfd, &ev) == -1)
        ERR_EXIT("epoll_ctl");

    //准备一个数组
    struct epoll_event events[2];
    int nread;

    while(1)
    {
        //该函数返回需要处理的事件数目，如返回0表示已超时。
        nread = epoll_wait(epollfd, events, 2, -1);
        if(nread == -1)
        {
            if(errno == EINTR)
                continue;
            ERR_EXIT("epoll_exit");
        }else if(nread == 0)
            continue;

        //开始检查每个fd
        int i;
        for(i = 0; i < nread; ++i)
        {
            int fd = events[i].data.fd;
            if(fd == STDIN_FILENO)
            {
                if(fgets(sendbuf, 1024, stdin) == NULL)
                {
                    shutdown(peerfd, SHUT_WR);
                    //移除stdin这个fd
                    struct epoll_event ev;
                    ev.data.fd = STDIN_FILENO;
                    //如果不删除描述符，下次循环进入后，发现该描述符存在，就会报错?????
                    
                    //创建好epoll句柄后，他就会占用一个fd值，
                    //在linux下/proc/进程id/fd/，是能够看到这个fd的
                    //所以在使用完epoll后，必须调用close关闭，
                    //否则可能导致fd被耗尽
                    

                    if(epoll_ctl(epollfd, EPOLL_CTL_DEL, STDIN_FILENO, &ev) == -1)
                        ERR_EXIT("epoll_ctl");
                }else
                {
                    writen(peerfd, sendbuf, strlen(sendbuf));
                    memset(sendbuf, 0x00, sizeof(sendbuf));
                }
            }
            if(fd == peerfd)//==写成了=
            {
                int ret = readline(peerfd, recvbuf, 1024);
                if(ret == -1)
                    ERR_EXIT("readline");
                else if(ret == 0)
                {
                    close(peerfd);
                    printf("server close\n");
                   // if(epoll_ctl(epollfd, EPOLL_CTL_DEL, peerfd, &ev) == -1)
                      //  ERR_EXIT("epoll_ctl");
                      // 这里已经exit退出了，不需要epoll_ctl，也就是不会有下次循环了
                    exit(EXIT_SUCCESS);
                }
                printf("recv data : %s", recvbuf);
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
