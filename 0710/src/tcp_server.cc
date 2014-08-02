#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/stat.h>
#include <fcntl.h>
#define ERR_EXIT(m)\
    do{\
        perror(m);\
        exit(EXIT_FAILURE);\
      }while(0);
typedef struct sockaddr* SA;
void do_service(int peer)
{
    char recvbuf[1024] = {0};
    while(1)
    {
        int iret = read(peer, recvbuf, 1024);
        if(iret == -1 && errno == EINTR)
        {
            continue;
        }
        else if(iret == -1)
        {
            ERR_EXIT("read");
        }
        else if(iret == 0)
        {
            close(peer);
            break;
        }
        else
        {
            write(peer, recvbuf, iret);
        }
    }
}
int main(int argc, const char *argv[])
{
    int fd_server, peer;
    fd_server = socket(PF_INET, SOCK_STREAM, 0);
    if(fd_server == -1)
    {
        ERR_EXIT("socket");
    }
    struct sockaddr_in seraddr;
    seraddr.sin_family = AF_INET;
    seraddr.sin_port = htons(8080);
    seraddr.sin_addr.s_addr = htonl(INADDR_ANY);
    socklen_t len = sizeof seraddr;

    if(bind(fd_server, (SA)&seraddr, len) == -1)
    {
        ERR_EXIT("bind");
    }
    if(listen(fd_server, SOMAXCONN) == -1)
    {
        ERR_EXIT("listen");
    }

    bzero(&peer, sizeof peer);
    len = sizeof peer;
    int fd_peer;
    fd_peer = accept(fd_server, (SA)&peer, &len);
    if(fd_peer == -1)
    {
        ERR_EXIT("accept");
    }
    do_service(peer);
    close(fd_server);

    return 0;
}
