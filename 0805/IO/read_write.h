#ifndef _READ_WRITE_H_
#define _READ_WRITE_H_ 
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
#include <arpa/inet.h>
#define ERR_EXIT(m)\
    do\
    {\
        perror(m);\
        exit(EXIT_FAILURE);\
    }while(0)
class ReadWrite 
{
    public:
        
        ssize_t readn(int, void*, size_t);
        ssize_t writen(int, void*, size_t);
        ssize_t recv_peek(int, void*, size_t);
        ssize_t readline(int, void*, size_t);

};

#endif  /*_READ_WRITE_H_*/
