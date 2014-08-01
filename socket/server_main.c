#include "network.h"
#include "socket.h"
#include "server.h"

int main(int argc, const char *argv[])
{
    if(signal(SIGPIPE, SIG_IGN) == SIG_ERR)
        ERR_EXIT("signal");
   // if(signal(SIGCHLD, handler) == SIG_ERR)
     //   ERR_EXIT("signal");

    int listenfd = get_listen_fd();
    printf("listen %d\n", listenfd);

    do_epoll(listenfd);

    close(listenfd);
    return 0;
}
