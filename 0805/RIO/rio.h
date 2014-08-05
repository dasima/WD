#ifndef _RIO_H_
#define _RIO_H_
#include <stdlib.h>
#define ERR_EXIT(m)\
    do\
    {\
        perror(m);\
        exit(EXIT_FAILURE);\
    }while(0)

class Rio
{
    public:
        Rio();
        ~Rio();

        ssize_t rio_read(char*, size_t);
        ssize_t rio_readn(char*, size_t);
        ssize_t rio_readline(char*, size_t);
        ssize_t roi_writen(char*, size_t);
    private:
        int fd_;
        int left_;
        char* bufPtr_;
        char buffer_[RIO_BUFFER];
};

#endif  /*_RIO_H_*/
