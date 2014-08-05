#include "poll_poll.h"
#include <errno.h>
#include <assert.h>
#include <iostream>
#include "read_write.h"
using namespace std;

ReadWrite rw1;

PollPoll::PollPoll(int listenfd)
    :listenfd_(listenfd),
    maxi_(-1),
    nready_(-1)
{
    int i;
    for(i = 0; i < 2048; ++i)
        clients_[i].fd = -1;
    clients_[0].fd = listenfd;
    clients_[0].events = POLLIN;
}

void PollPoll::setPollCallback(const PollCallback &pc)
{
    pollCallback_ = pc;    
}

void PollPoll::poll_wait()
{
    int nready;
    do
    {
        nready = poll(clients_, maxi_+1, -1);
    }while(nready == -1 && errno == EINTR);
    nready_ = nready;
    
}

void PollPoll::poll_accept()
{
    if(clients_[0].revents & POLLIN)
    {
        int peerfd = accept(listenfd_, NULL, NULL);
        if(peerfd == -1)
            ERR_EXIT("accept");
        poll_add_fd(peerfd);
    }
    
}

void PollPoll::poll_handle_data()
{
    int i;
    for(i = 1; i <= maxi_; ++i)
    {
        int fd = clients_[i].fd;
        if(fd == -1)
            continue;
        char recvbuf[1024] = {0};
        if(clients_[i].revents & POLLIN)
        {
            int ret = rw1.readline(fd, recvbuf, 1024);
            if(ret == -1)
                ERR_EXIT("readline");
            else if(ret == 0)
            {
                cout << "client close" << endl;
                poll_del_fd(i);
                continue;
            }

            pollCallback_();
        }
    }
}

void PollPoll::poll_add_fd(int peerfd)
{
    int i;
    for(i = 1; i < 2048; ++i)
    {
        if(clients_[i].fd == -1)
        {
            clients_[i].fd = peerfd;
            clients_[i].events = POLLIN;
            if(i > maxi_)
                maxi_ = i;
            break;
        }
    }
    if(i == 2048)
    {
        fprintf(stderr, "too many clients\n");
        exit(EXIT_FAILURE);
    }
}

void PollPoll::poll_del_fd(int i)
{
    assert(i >= 1 && i < 2048);
    close(clients_[i].fd);
    clients_[i].fd = -1;
}
