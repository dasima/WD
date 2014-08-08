#ifndef _TCP_CONNECTION_H_
#define _TCP_CONNECTION_H_
#include "rio.h"
#include "socket.h"
#include "non_copyable.h"
#include "inet_address.h"
#include <iostream>
#include <string>
#include <memory>
#include <functional>

class TcpConnection;
typedef std::shared_ptr<TcpConnection> TcpConnectionPtr;
class TcpConnection : private NonCopyable,
                      public std::enable_shared_from_this<TcpConnection>
{
    public:
        typedef std::function<void(const TcpConnectionPtr &)> TcpConnectionCallback;

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

        void setConnectionCallback(const TcpConnectionCallback &tc)
        { onConnectionCallback_ = tc; }
        void setMessageCallback(const TcpConnectionCallback &tc)
        { onMessageCallback_ = tc; }
        void setCloseCallback(const TcpConnectionCallback &tc)
        { onCloseCallback_ = tc; }

        void handleConnection()
        { onConnectionCallback_(shared_from_this());}
        void handleMessage()
        { std::cout << "on TcpConnectionCallback Message " << std::endl;
            onMessageCallback_(shared_from_this());}
        void handleClose()
        { onCloseCallback_(shared_from_this()); }
    private:
        Socket sockfd_;//fd
        Rio buffer_;//该连接的读写缓冲区

        TcpConnectionCallback onConnectionCallback_;//连接建立是的回调
        TcpConnectionCallback onMessageCallback_;//消息到达
        TcpConnectionCallback onCloseCallback_;//连接关闭
};

#endif  /*_TCP_CONNECTION_H_*/
