#include "select_t.h"
#include <assert.h>
void select_add_fd(Select_t *sel, int fd);
void select_del_fd(Select_t *sel, int fd);

void select_init(Select_t *sel, int listenfd)
{
    sel->listenfd_ = listenfd;
    FD_ZERO(&sel->allset_);
    FD_ZERO(&sel->rset_);
    FD_SET(listenfd, &sel->allset_);
    int i;
    for(i = 0; i < FD_SETSIZE; ++i)
        sel->clients_[i] = -1;
    sel->maxi_ = -1;
    sel->maxfd_ = listenfd;
    sel->handle_callback_ = NULL;
}

int select_wait(Select_t *sel)
{
    sel->rset_ = sel->allset_;
    int nready;
    do
    {
        nready = select(sel->maxfd_+1, &sel->rset_, NULL, NULL, NULL);
    }while(nready == -1 && errno == EINTR);
    if(nready == -1)
        ERR_EXIT("select");
    sel->nready_ = nready;
    return nready;
}

void select_accept(Select_t *sel)
{
    if(FD_ISSET(sel->listenfd_, &sel->rset_))
    {
        int peerfd = accept(sel->listenfd_, NULL, NULL);
        if(peerfd == -1)
            ERR_EXIT("accept");
        select_add_fd(sel, peerfd);
        --sel->nready_;
    }
}

void select_set_callback(Select_t *sel, void(*handler)(int, char*))
{
    sel->handle_callback_ = handler;
}


void select_handle_data(Select_t *sel)
{
    if(sel->nready_ == 0)
        return;
    int i;
    for(i = 0; i <= sel->maxi_; ++i)
    {
        //  int peerfd = sel->clients_[i];
        //        if(peerfd == -1)
        //          continue;
        if(FD_ISSET(sel->clients_[i], &sel->rset_))
        {
            int peerfd = sel->clients_[i];
            char recvbuf[1024] = {0};
            int ret = readline(peerfd, recvbuf, 1024);
            if(ret == -1)
                ERR_EXIT("readline");
            else if(ret == 0)
            {
                printf("client close\n");
                select_del_fd(sel, i);
                continue;
            }
            //调用用户自定义的逻辑
            sel->handle_callback_(peerfd, recvbuf);
        }
    }
}

void select_add_fd(Select_t *sel, int fd)
{
    int i;
    for(i = 0; i < FD_SETSIZE; ++i)
    {
        if(sel->clients_[i] == -1)
        {
            sel->clients_[i] = fd;
            if(i > sel->maxi_)
                sel->maxi_ = i;
            break;
        }
    }

    if(i == FD_SETSIZE)
    {   
        fprintf(stderr, "too many clients\n");
        exit(EXIT_FAILURE);
    }

    FD_SET(fd, &sel->allset_);
    if(fd > sel->maxfd_)
        sel->maxfd_ = fd;
}

void select_del_fd(Select_t *sel, int i)
{
    assert(i >= 0 && i < FD_SETSIZE);
    int fd = sel->clients_[i];
    close(fd);
    sel->clients_[i] = -1;
    FD_CLR(fd, &sel->allset_);
}
