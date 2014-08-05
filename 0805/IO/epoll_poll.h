#ifndef _EPOLL_POLL_H_
#define _EPOLL_POLL_H_

#include <sys/epoll.h>
class EpollPoll
{
    public:
        typedef function<void ()> EpollCallback;


        EpollPoll(int);
        ~EpollPoll();

        void epoll_do_wait();
        void epoll_do_accept();
        void epoll_do_handle();
        void epoll_handle_data(int);
       
    private:
        int epollfd_;
        int listenfd_;
        struct epoll_event events_[2048];
        int nready_;

        EpollCallback callback_;

};

#endif  /*_EPOLL_POLL_H_*/
