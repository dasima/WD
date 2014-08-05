#include "select_poll.h"
#include <assert.h>
#include "socket.h"
#include <iostream>
using namespace std;

ReadWrite rw;
SelectPoll::SelectPoll()
    :maxi_(-1),
     nready_(-1)
{
}

SelectPoll::SelectPoll(int listenfd)
    :maxi_(-1),
    maxfd_(listenfd),
    listenfd_(listenfd),
    nready_(-1)
{
    FD_ZERO(&allset_);
    FD_ZERO(&rset_);
    FD_SET(listenfd, &allset_);
    int i;
    for(i = 0; i < FD_SETSIZE; ++i)
        clients_[i] = -1;
}

SelectPoll::~SelectPoll()
{
    
}

void SelectPoll::setSelectCallback(const SelectCallback& sc)
{
    selectCallback_ = sc;
}

int SelectPoll::select_wait()
{
    rset_ = allset_;
    int nready;
    do
    {
        nready = select(maxfd_ + 1, &rset_, NULL, NULL, NULL);
    }while(nready == -1 && errno == EINTR);
    if(nready == -1)
        ERR_EXIT("select");
    nready_ = nready;
    return nready;
}

void SelectPoll::select_accept()
{
    if(FD_ISSET(listenfd_, &rset_))
    {
        int peerfd = accept(listenfd_, NULL, NULL);
        if(peerfd == -1)
            ERR_EXIT("accept");
        select_add_fd(peerfd);
        --nready_;
    }
}

void SelectPoll::select_handle_data()
{
    if(nready_ == 0)
        return ;
    int i;
    for(i = 0; i <= maxi_; ++i)
    {
        if(FD_ISSET(clients_[i], &rset_))
        {
            int peerfd = clients_[i];
            char recvbuf[1024] = {0};
            cout << "readline..." << endl;
            int ret = rw.readline(peerfd, recvbuf, 1024);

            cout << "ret ---" << ret << endl;
            cout << "after readline..." << endl;
            if(ret == -1)
                ERR_EXIT("readline");
            else if(ret == 0)
            {
                cout << "client close " << endl;
                select_del_fd(i);
                continue;
            }
            selectCallback_();
        }
    }
}

void SelectPoll::select_add_fd(int fd)
{
    int i;
    for(i = 0; i < FD_SETSIZE; ++i)
    {
        if(clients_[i] == -1)
        {
            clients_[i] = fd;
            if(i > maxi_)
                maxi_ = i;
            break;
        }
    }
    if(i == FD_SETSIZE)
    {
        cout << "error, too many clients" << endl;
        exit(EXIT_FAILURE);
    }
    FD_SET(fd, &allset_);
    if(fd > maxfd_)
        maxfd_ = fd;
}

void SelectPoll::select_del_fd(int i)
{
    assert(i >= 0 && i < FD_SETSIZE);
    int fd = clients_[i];
    close(fd);
    clients_[i] = -1;
    FD_CLR(fd, &allset_);
}



