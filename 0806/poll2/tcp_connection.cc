#include "tcp_connection.h"
#include <iostream>
using namespace std;

TcpConnection::TcpConnection(int fd)
    :sockfd_(fd), buffer_(fd)
{
}

TcpConnection::~TcpConnection()
{
    shutdown();
}

ssize_t TcpConnection::readn(char* usrbuf, size_t n)
{
    int nready;
    nready = buffer_.rio_readn(usrbuf, n);
    if(nready == -1)
        ERR_EXIT("readn");
    return nready;
}

ssize_t TcpConnection::readLine(char *usrbuf, size_t n)
{
    int nready;
    nready = buffer_.rio_readline(usrbuf, n);
    if(nready == -1)
        ERR_EXIT("readline");
    return nready;
}

ssize_t TcpConnection::writen(const char *usrbuf, size_t n)
{
    int nwrite = buffer_.rio_writen(usrbuf, n);
    if(nwrite == -1)
        ERR_EXIT("writen");
    return nwrite;
}

void TcpConnection::sendString(const std::string &s)
{
    writen(s.c_str(), s.size());
}

std::string TcpConnection::receiveString()
{
    char buf[1024];
    readLine(buf, 1024);
    return std::string(buf);
}

void TcpConnection::shutdown()
{
    sockfd_.shutdownWrite();    
}
    
