#include "network.h"
#include "socket.h"
#include "epoll_t.h"
#include <sys/epoll.h>
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

    Epoll_t epo;
    epoll_init(&epo, listenfd, handler);
    while(1)
    {
        epoll_do_wait(&epo);
        epoll_handle(&epo);
    }
    epoll_close(&epo);

    close(listenfd);
    
    return 0;
}
