#include "epoll_poll.h"

EpollPoll::EpollPoll(int listenfd)
    :nready_(0),
    listenfd_(listenfd)
{
    if((epollfd_ = epoll_create(2048)) == -1)
        ERR_EXIT("epoll_create");
    epoll_add_fd(listenfd);

}

EpollPoll::~EpollPoll()
{
    close(epollfd_);
    close(listenfd_);
}

void EpollPoll::epoll_do_wait()
{
    int nready;
    do
    {
        nready = epoll_wait(epollfd_, events_, 2048, -1);
        
    }while(nready == -1 && errno == EINTR);
    if(nready == -1)
        ERR_EXIT("epoll_wait");
    nready_ = nready;
}

void EpollPoll::epoll_do_handle()
{
    int i;
    for(i = 0; i < nready_; ++i)
    {
        int fd = events_[i].data.fd;
        if(fd == listenfd_)
            epoll_do_accept();
        else
            epoll_handle_data(fd);
    }
}

void EpollPoll::epoll_do_accept()
{
    int peerfd = accept(listenfd_, NULL, NULL);
    if(peerfd == -1)
        ERR_EXIT("accept");
    epoll_add_fd(peerfd);
}

void EpollPoll::epoll_handle_data(int fd)
{
    char recvbuf[1024];
    int ret = readline(fd, recvbuf, 1024);
    if(ret == -1)
        ERR_EXIT("readline");
    else if(ret == 0)
    {
        printf("client close\n");
        epoll_del_fd(fd);
        return ;
    }
    callback_();
}

void EpollPoll::epoll_add_fd(int fd)
{
    struct epoll_event ev;
    ev.data.fd = fd;
    ev.events = EPOLLIN;
    if(epoll_ctl(epollfd_, EPOLL_CTL_ADD, fd, &ev) == -1)
        ERR_EXIT("epoll_ctl");
}

void epoll_del_fd(int fd)
{
    struct epoll_event ev;
    ev.data.fd = fd;
    if(epoll_ctl(epollfd_, EPOLL_CTL_DEL, fd, &ev) == -1)
        ERR_EXIT("epoll_ctl");
}
