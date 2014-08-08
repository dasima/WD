#include "poll_poller.h"
#include <iostream>
#include <assert.h>
using namespace std;

#define ERR_EXIT(m) \
    do { \
        perror(m);\
        exit(EXIT_FAILURE);\
    }while(0)
PollPoller::PollPoller(int listenfd)
    :listenfd_(listenfd),
    maxi_(0),
    nready_(0)
{
    int i;
    for(i = 0; i < 2048; ++i)
        event_[i].fd = -1;
    event_[0].fd = listenfd;
    event_[0].events = POLLIN;
}

void PollPoller::pollWait()
{
    int nready;
    do
    {
        nready = ::poll(event_, maxi_ + 1, 10000);
    }while(nready == -1 && errno == EINTR);
    if(nready == -1)
        ERR_EXIT("poll");
    nready_ = nready;
}

void PollPoller::handleAccept()
{
    if(event_[0].revents && POLLIN)
    {
        int peerfd = ::accept(listenfd_, NULL, NULL);;
        cout << "handleAccept " << peerfd << endl;
        if(peerfd == -1)
            ERR_EXIT("accept");
        handleConnectionEvent(peerfd);
    }
}

void PollPoller::handleData()
{
    int i;
    for(i = 1; i <= maxi_; ++i)
    {
        int peerfd = event_[i].fd;
        if(peerfd == -1)
            continue;
        if(event_[i].revents & POLLIN)
        {
            char buf[1024];
            int nread = ::recv(peerfd, buf, sizeof buf, MSG_PEEK);
            cout << "handleData " << nread << endl;
            if(nread == -1)
                ERR_EXIT("recv");
            else if(nread == 0)
            {
                handleCloseEvent(i);
            }
            else
                handleMessageEvent(peerfd);
        }
    }
}

void PollPoller::handleConnectionEvent(int peerfd)
{
    //
    int i;
    for(i = 1; i < 2048; ++i)
    {
        if(event_[i].fd == -1)
        {
            event_[i].fd = peerfd;
            event_[i].events = POLLIN;
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
    cout << "i " << i << endl;

    TcpConnectionPtr conn(new TcpConnection(peerfd));
    conn->setConnectionCallback(onConnectionCallback_);
    conn->setMessageCallback(onMessageCallback_);
    conn->setCloseCallback(onCloseCallback_);

    lists_.insert(make_pair(peerfd, conn));
    conn->handleConnection();
}

void PollPoller::handleMessageEvent(int peerfd)
{
    TcpConnectionIterator it = lists_.find(peerfd);
    cout << "handleMessage " << endl;
    assert(it != lists_.end());
    it->second->handleMessage();
}

void PollPoller::handleCloseEvent(int i)
{
    assert(i >= 0 && i <= 2048);
    int peerfd = event_[i].fd;
    TcpConnectionIterator it = lists_.find(peerfd);
    assert(it != lists_.end());
    it->second->handleClose();
    lists_.erase(it);

    event_[i].fd = -1;
}
