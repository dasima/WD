#include "network.h"
#include "socket.h"
#include <sys/epoll.h>

void do_epoll(int listenfd);
int main(int argc, const char *argv[])
{
    if(signal(SIGPIPE, SIG_IGN) == SIG_ERR)
        ERR_EXIT("signal");

    int listenfd = get_listen_fd();

    do_epoll(listenfd);

    close(listenfd);

    return 0;
}

void do_epoll(int listenfd)
{
    //创建epoll
    int epollfd = epoll_create(2048);
    if(epollfd == -1)
        ERR_EXIT("epoll_create");

    //添加listenfd
    struct epoll_event ev;
    ev.data.fd = listenfd;
    ev.events = EPOLLIN;
    if(epoll_ctl(epollfd, EPOLL_CTL_ADD, listenfd, &ev) == -1)
        ERR_EXIT("epoll_ctl");

    //创建数组
    struct epoll_event events[2048];
    int nread;

    while(1)
    {
        //wait
        nread = epoll_wait(epollfd, events, 2048, -1);
        if(nread == -1)
        {
            if(errno == EINTR)
                continue;
            ERR_EXIT("epoll_wait");
        }

        //遍历events数组
        int i;
        for(i = 0; i < nread; ++i)
        {
            int fd = events[i].data.fd;
            //如果是listenfd
            if(fd == listenfd)
            {
                int peerfd = accept(listenfd, NULL, NULL);
                if(peerfd == -1)
                {
                    ERR_EXIT("accept");
                }
                //加入epoll
                struct epoll_event ev;
                ev.data.fd = peerfd;
                ev.events = EPOLLIN;
                if(epoll_ctl(epollfd, EPOLL_CTL_ADD, peerfd, &ev) == -1)
                    ERR_EXIT("epoll_ctl");
            }else//如果是普通fd
            {
                int peerfd = events[i].data.fd;
                char recvbuf[1024] = {0};
                int ret = readline(peerfd, recvbuf, 1024);
                if(ret == -1)
                {
                    ERR_EXIT("readline");
                }else if(ret == 0)
                {
                    printf("client close\n");
                    //从epoll中删除
                    struct epoll_event ev;
                    ev.data.fd = peerfd;
                    if(epoll_ctl(epollfd, EPOLL_CTL_DEL, peerfd, &ev) == -1)
                        ERR_EXIT("epoll_ctl");
                    close(peerfd);
                    continue;
                }

                printf("recv data %s", recvbuf);
                writen(peerfd, recvbuf, strlen(recvbuf));
            }
        }
    }
    //关闭epoll句柄
    close(epollfd);
}
