#include "network.h"
#include "socket.h"
#include "poll_t.h"

void handler(int fd, char* buf)
{
    printf("recv data %s", buf);
    writen(fd, buf, strlen(buf));
}

int main(int argc, const char *argv[])
{
    if(signal(SIGPIPE, SIG_IGN) == SIG_ERR)
        ERR_EXIT("signal");

    int listenfd = get_listen_fd();

    Poll_t pol;
    poll_init(&pol, listenfd, handler);
    while(1)
    {
        poll_wait(&pol);
        poll_accept(&pol);
        poll_handle_data(&pol);
    }

    close(listenfd);

    return 0;
}
