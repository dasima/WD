#ifndef _TCP_CONNECTION_H_
#define _TCP_CONNECTION_H_
#include <iostream>
#include <string>
#include <memory>
#include "rio.h"
#include "socket.h"

class TcpConnection;
typedef std::shared_ptr<TcpConnection> TcpConnectionPtr;
class TcpConnection : private NonCopyable
{
    public:
        explicit TcpConnection(int);
        ~TcpConnection();

        int fd() const
        {return sockfd_.fd();}
        
        ssize_t readn(char *, size_t);
        ssize_t readLine(char*, size_t);
        ssize_t writen(const char*, size_t);
        void sendString(const std::string &);
        std::string receiveString();

        void shutdown();
    private:
        Socket sockfd_;
        Rio buffer_;
};

#endif  /*_TCP_CONNECTION_H_*/
