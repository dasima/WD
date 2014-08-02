#ifndef _SELECT_T_H_
#define _SELECT_T_H_ 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <errno.h>
#include <signal.h>
#include <sys/select.h>
#define ERR_EXIT(m)\
    do\
    {\
        perror(m);\
        exit(EXIT_FAILURE);\
    }while(0)

typedef struct {
    fd_set allset_;
    fd_set rset_;
    int clients_[FD_SETSIZE];
    int maxi_;
    int maxfd_;
    int nready_;
    int listenfd_;
    void (*handle_callback_)(int, char*);
}Select_t;

void select_init(Select_t *sel, int listenfd);
void select_set_callback(Select_t *sel, void(*handle_callback)(int, char*));
int select_wait(Select_t *sel);
void select_accept(Select_t *sel);
void select_handle_data(Select_t *sel);

#endif  /*_SELECT_T_H_*/
