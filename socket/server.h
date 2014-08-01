#ifndef _SERVER_H_
#define _SERVER_H_ 
#include <netinet/in.h>
#include <sys/select.h>
#include <poll.h>
#include <sys/epoll.h>
void do_service(int);
void handler(int);
void do_process(int);

void*thread_func(void*);
void do_thread(int);

void do_select(int);

void do_poll(int);

#endif  /*_SERVER_H_*/
