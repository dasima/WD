#ifndef _POLL_POLL_H_
#define _POLL_POLL_H_ 

#include <sys/types.h>
#include <sys/socket.h>
#include <functional>
#include <poll.h>
#define ERR_EXIT(m)\
    do\
    {\
        perror(m);\
        exit(EXIT_FAILURE);\
    }while(0)

class PollPoll
{
    public:
        typedef std::function<void ()> PollCallback;

        PollPoll(int);

        void setPollCallback(const PollCallback &);
        void poll_wait();
        void poll_accept();
        void poll_handle_data();
    private:
        void poll_add_fd(int);
        void poll_del_fd(int);

        struct pollfd clients_[2048];
        int listenfd_;
        int maxi_;
        int nready_;
        
        PollCallback pollCallback_;
};

#endif  /*_POLL_POLL_H_*/
