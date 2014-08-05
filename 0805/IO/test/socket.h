#ifndef _SOCKET_H_
#define _SOCKET_H_ 

#include "read_write.h"
#include <netinet/in.h>
#include <sys/select.h>
int getListenFd()
{
    //创建socket套接字
    int listenfd = socket(PF_INET, SOCK_STREAM, 0);
    if(listenfd == -1)
        ERR_EXIT("SOCKET");

    //设置端口复用
    int on = 1; 
    if(setsockopt(listenfd, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on)) < 0)
        ERR_EXIT("setsockopt");

    struct sockaddr_in serveraddr;
    serveraddr.sin_family = AF_INET;
    serveraddr.sin_port = htons(8080);
    serveraddr.sin_addr.s_addr = htonl(INADDR_ANY);

    //bind绑定端口
    if(bind(listenfd, (struct sockaddr*)&serveraddr, sizeof serveraddr) < 0)
        ERR_EXIT("bind");

    //listen监听端口
    if(listen(listenfd, SOMAXCONN) < 0)
        ERR_EXIT("listen");

    return listenfd;
}

#endif  /*_SOCKET_H_*/
