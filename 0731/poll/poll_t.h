#ifndef _POLL_T_H_
#define _POLL_T_H_ 
#include <poll.h>
typedef struct
{
    struct pollfd clients_[2048];
    int listenfd_;
    int maxi_;//最大的数组下标
    int nready_;
    void (*handle_callback_)(int, char*);//回调函数
}Poll_t;

void poll_init(Poll_t *pol, int listenfd, void(*handler)(int, char*));
void poll_wait(Poll_t *pol);
void poll_accept(Poll_t *);
void poll_handle_data(Poll_t *);


#endif  /*_POLL_T_H_*/
