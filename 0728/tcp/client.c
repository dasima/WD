#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <errno.h>

#define ERR_EXIT(m) \
    do { \
        perror(m);\
        exit(EXIT_FAILURE);\
    }while(0)

do_service(int peerfd)
{
    char recvbuf[1024] = {0};
    char sendbuf[1024] = {0};
    int ret;

    while(1)
    {
        if(fgets(sendbuf, 1024, stdin) != NULL)
        {
            write(peerfd, sendbuf, strlen(sendbuf));
            ret = read(peerfd, recvbuf, 1000);
            if(ret == -1)
            {
                if(errno == EINTR)
                    continue;
                return;

            }else if(ret == 0)
                break;
            printf("recive data : %s", recvbuf);

        }
        memset(recvbuf, 0, sizeof recvbuf);
        memset(sendbuf, 0, sizeof sendbuf);
    }
}

int main(int argc, const char *argv[])
{
    //创建套接字socket
    int peerfd = socket(AF_INET, SOCK_STREAM, 0);
    if(peerfd == -1)
        ERR_EXIT("socket");

    struct sockaddr_in peeraddr;
    peeraddr.sin_family = AF_INET;
    peeraddr.sin_port = htons(8080);
    peeraddr.sin_addr.s_addr = inet_addr("127.0.0.1");

    //建立连接connect
    if((connect(peerfd, (struct sockaddr*)&peeraddr, sizeof peeraddr)) < 0)
        ERR_EXIT("connect");

    do_service(peerfd);

    close(peerfd);
    return 0;
}
