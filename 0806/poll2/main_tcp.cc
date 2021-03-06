#include "tcp_connection.h"
#include <iostream>
#include <string>
#include <vector>
using namespace std;

#define ERR_EXIT(m) \
    do { \
        perror(m);\
        exit(EXIT_FAILURE);\
    }while(0)

int get_listen_fd();

void onMessage(const TcpConnectionPtr &conn)
{
    conn->shutdown();
}

void onClose(const TcpConnectionPtr &conn)
{
    conn->shutdown();
}
/*
 *这个函数有问题，一直进行调用tcpConnectionCallback,
 *形成了深度调用
 */

int main(int argc, const char *argv[])
{
    int listenfd = get_listen_fd();
    if(listenfd == -1)
        ERR_EXIT("listenfd");
    int peerfd = accept(listenfd, NULL, NULL);
    if(peerfd == -1)
        ERR_EXIT("accept");

    TcpConnectionPtr conn(new TcpConnection(peerfd));
    conn->setMessageCallback(onMessage);
    char buf[1024];
    while(1)
    {
        conn->handleMessage();
    }

    return 0;
}

int get_listen_fd()
{
    int listenfd = ::socket(PF_INET, SOCK_STREAM, 0);
    if(listenfd == -1)
        ERR_EXIT("socket");

    int on = 1;
    if(::setsockopt(listenfd, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on)) < 0)
        ERR_EXIT("setsockopt");

    struct sockaddr_in serveraddr;
    serveraddr.sin_family = AF_INET;
    serveraddr.sin_port = htons(8080);
    serveraddr.sin_addr.s_addr = htonl(INADDR_ANY);

    if(::bind(listenfd, (struct sockaddr*)&serveraddr, sizeof(serveraddr)) < 0)
        ERR_EXIT("bind");

    if(::listen(listenfd, SOMAXCONN) < 0)
        ERR_EXIT("listen");

    return listenfd;
}
