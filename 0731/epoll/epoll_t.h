#ifndef EPOLL_T_H_
#define EPOLL_T_H_ 
#include <sys/epoll.h>
typedef struct 
{
    int epollfd_;
    int listenfd_;
    struct epoll_event events_[2048];
    int nready_;
    void (*handle_callback_)(int, char*);
}Epoll_t;

void epoll_init(Epoll_t *epoll, 
        int listenfd,
        void (*handler)(int, char*));
void epoll_do_wait(Epoll_t *);
void epoll_handle(Epoll_t *);
void epoll_accept(Epoll_t *);
void epoll_handle_data(Epoll_t *, int);
void epoll_close(Epoll_t *);

#endif  /*EPOLL_T_H_*/
