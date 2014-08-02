#ifndef _NETWORK_H_
#define _NETWORK_H_ 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/time.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <errno.h>
#include <signal.h>
#include <netinet/in.h>
#define ERR_EXIT(m)\
    do\
    {\
        perror(m);\
        exit(EXIT_FAILURE);\
    }while(0)
ssize_t readn(int fd, void* usrbuf, size_t n);
ssize_t writen(int fd, void*, size_t);
ssize_t recv_peek(int, void*, size_t);
ssize_t readline(int, void*, size_t);

#endif  /*_NETWORK_H_*/
