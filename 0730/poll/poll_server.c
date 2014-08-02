#include "network.h"
#include "socket.h"
#include <poll.h>
    
void do_poll(int listenfd);
int main(int argc, const char *argv[])
{
    if(signal(SIGPIPE, SIG_IGN) == SIG_ERR)
        ERR_EXIT("signal");

    int listenfd = get_listen_fd();

    do_poll(listenfd);

    close(listenfd);
    
    return 0;
}

void do_poll(int listenfd)
{
    struct pollfd client[2048];
    int i;
    for(i = 0; i < 2048; ++i)
    {
        client[i].fd = -1;
    }

    client[0].fd = listenfd;
    client[0].events = POLLIN;
    int max = 0;//最大数组下标
    int nready;

    while(1)
    {
        //poll
        nready = poll(client, max + 1, -1);
        if(nready == -1)
        {
            if(errno == EINTR)
                continue;
            ERR_EXIT("poll");
        }else if(nready == 0)
            continue;
        //listen
        if(client[0].revents & POLLIN)
        {
            int peerfd = accept(client[0].fd, NULL, NULL);
            if(peerfd == -1)
                ERR_EXIT("accept");

            int i = 1;
            for(i = 1; i < 2048; ++i)
            {
                if(client[i].fd == -1)
                {
                    client[i].fd = peerfd;
                    client[i].events = POLLIN;
                    if(i > max)
                        max = i;
                    break;
                }
            }
            if(i == 2048)
            {
                fprintf(stderr, "too many clients\n");
                exit(EXIT_FAILURE);
            }
            if(--nready <= 0)
                continue;
        }

        //clients
        int i;
        for(i = 1; i <= max; ++i)
        {
            int fd = client[i].fd;
            if(fd == -1)
                continue;
            char recvbuf[1024] = {0};
            if(client[i].revents & POLLIN)
            {
                int ret = readline(fd, recvbuf, 1024);
                if(ret == -1)
                    ERR_EXIT("readline");
                else if(ret == 0)
                {
                    close(fd);
                    client[i].fd = -1;
                    continue;
                }

                printf("recv data : %s", recvbuf);
                writen(fd, recvbuf, strlen(recvbuf));

                if(--nready <= 0)
                    break;
            }
        }
    }
}
