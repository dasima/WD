#ifndef _SELECT_POLL_H_
#define _SELECT_POLL_H_
#include <sys/select.h>
#include <sys/types.h>
#include <sys/time.h>
#include <unistd.h>
#include <iostream>
#include <functional>

class SelectPoll
{
    public:
        typedef std::function<void ()> SelectCallback;

        SelectPoll();
        SelectPoll(int);
        ~SelectPoll();

        void setSelectCallback(const SelectCallback &);
        int select_wait();
        void select_accept();
        void select_handle_data();
    private:
        void select_add_fd(int);
        void select_del_fd(int);

        SelectCallback selectCallback_;
        fd_set allset_;
        fd_set rset_;
        int clients_[FD_SETSIZE];
        int maxi_;
        int maxfd_;
        int nready_;
        int listenfd_;
};

#endif  /*_SELECT_POLL_H_*/
