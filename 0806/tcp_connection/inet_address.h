#ifndef _INET_ADDRESS_H_
#define _INET_ADDRESS_H_

#include"copyable.h"
#include <netinet/in.h>
#include <string.h>
typedef struct sockaddr SA;
class InetAddress : private Copyable
{
    public:
        explicit InetAddress(uint16_t);
        InetAddress(const struct sockaddr_in &);

        const struct sockaddr_in *getSockAddrInet() const
        {return &addr_;}
        void setSockAddrInet(const struct sockaddr_in &addr)
        {addr_ = addr;}

        uint32_t ipNetEndian() const
        {return addr_.sin_addr.s_addr;}
        uint16_t portNetEndian() const
        {return addr_.sin_port;}
    private:
        struct sockaddr_in addr_;
};

inline InetAddress::InetAddress(uint16_t port)
{
    ::memset(&addr_, 0, sizeof addr_);
    addr_.sin_family = AF_INET;
    addr_.sin_addr.s_addr = INADDR_ANY;
    addr_.sin_port = ::htons(port);
}

inline InetAddress::InetAddress(const struct sockaddr_in &addr)
    :addr_(addr)
{
}

#endif  /*_INET_ADDRESS_H_*/
