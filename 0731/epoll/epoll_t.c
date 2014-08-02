#include "network.h"
#include "socket.h"
#include "epoll_t.h"
#include <sys/epoll.h>
void epoll_add_fd(Epoll_t *epo, int fd);
void epoll_del_fd(Epoll_t *epo, int fd);

void epoll_init(Epoll_t * epo, 
        int listenfd,
        void (*handler)(int, char*))
{
    if((epo->epollfd_ = epoll_create(2048)) == -1)
    {
        ERR_EXIT("epoll_create");
    }
    epo->nready_ = 0;
    epo->listenfd_ = listenfd;
    epoll_add_fd(epo, listenfd);
    epo->handle_callback_ = handler;
}

void epoll_close(Epoll_t *epo)
{
    close(epo->epollfd_);
    close(epo->listenfd_);
}

void epoll_do_wait(Epoll_t *epo)
{
    int nready;
    do
    {
        nready = epoll_wait(epo->epollfd_,
                epo->events_,
                2048,
                -1);
    }while(nready == -1 && errno == EINTR);
    if(nready == -1)
        ERR_EXIT("epoll_wait");
    epo->nready_ = nready;
}

void epoll_handle(Epoll_t *epo)
{
    int i;
    for(i = 0; i < epo->nready_; ++i)
    {
        int fd = epo->events_[i].data.fd;
        if(fd == epo->listenfd_)
            epoll_accept(epo);
        else
            epoll_handle_data(epo, fd);
    }
}

void epoll_accept(Epoll_t *epo)
{
    int peerfd = accept(epo->listenfd_, NULL, NULL);
    if(peerfd == -1)
        ERR_EXIT("accept");
    epoll_add_fd(epo, peerfd);
}

void epoll_handle_data(Epoll_t *epo, int peerfd)
{
    char recvbuf[1024];
    int ret = readline(peerfd, recvbuf, 1024);
    if(ret == -1)
        ERR_EXIT("readline");
    else if(ret == 0)
    {
        printf("client close\n");
        epoll_del_fd(epo, peerfd);
        return;
    }
    epo->handle_callback_(peerfd, recvbuf);
}

void epoll_add_fd(Epoll_t *epo, int fd)
{
    struct epoll_event ev;
    ev.data.fd = fd;
    ev.events = EPOLLIN;
    if(epoll_ctl(epo->epollfd_, EPOLL_CTL_ADD, fd, &ev) == -1)
        ERR_EXIT("epoll_ctl");
}

void epoll_del_fd(Epoll_t *epo, int fd)
{
    struct epoll_event ev;
    ev.data.fd = fd;
    if(epoll_ctl(epo->epollfd_, EPOLL_CTL_DEL, fd, &ev) == -1)
        ERR_EXIT("epoll_ctl");
}
