#include "tcp_connection.h"
#include "poll_poller.h"
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

void onConnection(const TcpConnectionPtr &conn)
{
    conn->sendString("hello\n");
}

void onMessage(const TcpConnectionPtr &conn)
{
    string s(conn->receiveString());
    cout << "recv data " << s;
    conn->sendString(s);
}

void onClose(const TcpConnectionPtr &conn)
{
    cout << "close conn " << endl;
    conn->shutdown();
}
/*
 *
 */

int main(int argc, const char *argv[])
{
    int listenfd = get_listen_fd();
    if(listenfd == -1)
        ERR_EXIT("listenfd");

    PollPoller poller(listenfd);
    poller.setConnectionCallback(onConnection);
    poller.setMessageCallback(onMessage);
    poller.setCloseCallback(onClose);

    while(1)
    {
        poller.pollWait();
        poller.handleAccept();
        poller.handleData();
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
