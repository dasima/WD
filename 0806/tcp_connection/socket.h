#ifndef _SOCKET_H_
#define _SOCKET_H_

#include "non_copyable.h"
#include "inet_address.h"

class Socket : private NonCopyable
{
    public:
        explicit Socket(int);
        ~Socket();

        int fd() const
        {return sockfd_;}
        void bindAddress(const InetAddress &addr);
        void listen();
        int accept();
        void shutdownWrite();
        void setReusePort();
    private:
        const int sockfd_;
};


#endif  /*_SOCKET_H_*/
