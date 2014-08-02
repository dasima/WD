#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <errno.h>
#include <signal.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#define ERR_EXIT(m) \
    do { \
        perror(m);\
        exit(EXIT_FAILURE);\
    }while(0)

void do_service(int peerfd)
{
    char recvbuf[1042] = {0};
    int ret;
    while(1)
    {
        memset(recvbuf, 0, sizeof recvbuf);
        ret = read(peerfd, recvbuf, 1000);
        if(ret == -1)
        {
            if(errno == EINTR)
                continue;
            return ;
        }else if(ret == 0 )
            break;
        else
        {
            write(peerfd, recvbuf, strlen(recvbuf));
        }

    }
}


int main(int argc, const char *argv[])
{
    int listenfd = socket(AF_INET, SOCK_STREAM, 0);
    if(listenfd == -1)
        ERR_EXIT("socket");

    //设置端口复用
    int on = 1;
    if(setsockopt(listenfd, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on)))
        ERR_EXIT("setsockopt");

    struct sockaddr_in serveraddr;
    serveraddr.sin_family = AF_INET;
    serveraddr.sin_port = htons(8080);
    serveraddr.sin_addr.s_addr = htonl(INADDR_ANY);

    if((bind(listenfd, (struct sockaddr*)&serveraddr, sizeof serveraddr)) == -1)
        ERR_EXIT("bind");

    if(listen(listenfd, SOMAXCONN) < 0)
        ERR_EXIT("listen");

    int peerfd;
    if((peerfd = accept(listenfd, NULL, NULL)) < 0)
        ERR_EXIT("accept");

    do_service(peerfd);

    close(peerfd);
    close(listenfd);
    return 0;
}