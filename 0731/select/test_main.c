#include "network.h"
#include "select_t.h"
#include "socket.h"

void handler(int listenfd, char* recvbuf)
{
    printf("recv data : %s", recvbuf);
    writen(listenfd, recvbuf, strlen(recvbuf));
}

int main(int argc, const char *argv[])
{
    if(signal(SIGPIPE, SIG_IGN) == SIG_ERR)
        ERR_EXIT("signal");

    int listenfd = get_listen_fd();

    Select_t sel;
    select_init(&sel, listenfd);
    select_set_callback(&sel, handler);
    while(1)
    {
        select_wait(&sel);
        select_accept(&sel);
        select_handle_data(&sel);
    }
    close(listenfd);
    return 0;
}
