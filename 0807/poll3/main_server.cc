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



void onMessage(const TcpConnectionPtr &conn)
{
    conn->receiveString();
    conn->sendString("ACK\n");
}

/*
 *
 */

int main(int argc, const char *argv[])
{
    int listenfd = ::socket(PF_INET, SOCK_STREAM, 0);
    if(listenfd == -1)
        ERR_EXIT("listenfd");

    Socket sock(listenfd);
    InetAddress addr(8080);
    sock.setReusePort();
    sock.bindAddress(addr);
    sock.listen();

    PollPoller poller(sock.fd());
    poller.setMessageCallback(&onMessage);

    while(1)
    {
        poller.pollWait();
        poller.handleAccept();
        poller.handleData();
    }

    return 0;
}

