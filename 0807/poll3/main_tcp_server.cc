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


void onConnection(const TcpConnectionPtr &conn)
{
    conn->sendString("hello\n");
}

void onMessage(const TcpConnectionPtr &conn)
{
    cout << "recv data " << conn->receiveString();
    conn->sendString("ACK\n");
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
    InetAddress addr(8080);
    TcpServer server(addr);
    server.setConnection(&onConnection);
    server.setMessage(&onMessage);
    server.start();

    return 0;
}

