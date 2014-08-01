#include "network.h"
#include "server.h"
#include "socket.h"
void do_service(int peerfd)
{
    char recvbuf[1024] = {0};
    int ret;
    while(1)
    {
        ret = readline(peerfd, recvbuf, 1024);
        if(ret == 0)
        {
            close(peerfd);
            exit(EXIT_SUCCESS);
        }
        printf("recv data : %s", recvbuf);
        writen(peerfd, recvbuf, sizeof(recvbuf));
    }
}

void handler(int sig)
{
    while(waitpid(-1, NULL, WNOHANG) > 0)
        ;
}

void do_process(int listenfd)
{
    struct sockaddr_in peeraddr;
    memset(&peeraddr, 0, sizeof(peeraddr));
    socklen_t len ;
    int peerfd = accept(listenfd, (struct sockaddr*)&peeraddr, &len);
    if(peerfd == -1)
        ERR_EXIT("accept");

    pid_t pid;
    if((pid = fork()) < 0)
        ERR_EXIT("fork");
    else if(pid == 0)
    {
        close(listenfd);
        do_service(peerfd);
        exit(EXIT_SUCCESS);
    }
    close(peerfd);
}



void *thread_func(void* arg)
{
    int *pfd = (int*)arg;
    int peerfd = *pfd;
    free(pfd);
    pthread_detach(pthread_self());
    do_service(peerfd);
    close(peerfd);
}

void do_thread(int listenfd)
{
    int peerfd = accept(listenfd, NULL, NULL);
    if(peerfd == -1)
        ERR_EXIT("accept");
    int *pfd = (int*)malloc(sizeof(int));
    if(pfd == NULL)
        ERR_EXIT("malloc");
    *pfd = peerfd;

    pthread_t tid;
    if(pthread_create(&tid, NULL, thread_func, pfd))
        free(pfd);
}


void do_select(int listenfd)
{
    //准备一些初始化参数
    fd_set allset;//用来备份rset
    fd_set rset;
    int client[FD_SETSIZE];//保存已连接的客户fd
    int i;
    for(i = 0; i < FD_SETSIZE; ++i)
    {
        client[i] = -1;
    }
    int maxi = -1;//代表client中的最大下标
    int nready;
    int maxfd = listenfd;
    FD_ZERO(&allset);
    FD_ZERO(&rset);
    FD_SET(listenfd, &allset);

    while(1)
    {
        //初始化rset
        rset = allset;

        //select
        //这里的rset既是输入参数，也是输出参数
        nready = select(maxfd + 1, &rset, NULL, NULL, NULL);
        if(nready == -1)
        {
            if(errno == EINTR)
                continue;
            ERR_EXIT("select");
        }else if(nready == 0)
            continue;

        //判断listenfd，是否在监听中
        if(FD_ISSET(listenfd, &rset))
        {
            //accept接受连接
            int peerfd = accept(listenfd, NULL, NULL);
            if(peerfd == -1)
                ERR_EXIT("accept");

            //将接受请求的peerfd加入client，
            //同时处理client满的情况
            int i;
            for(i = 0; i < FD_SETSIZE; ++i)
            {
                if(client[i] == -1)
                {
                    client[i] = peerfd;
                    if(i > maxi)
                        maxi = i;//更新最大下标
                    break;//如果没有新的peerfd加入，则不需要处理，退出这一循环
                }
            }
            if(i == FD_SETSIZE)
            {
                fprintf(stderr, "too many clients\n");
                exit(EXIT_FAILURE);
            }

            //这里正式将peerfd加入allset中
            FD_SET(peerfd, &allset);
            if(peerfd > maxfd)
                maxfd = peerfd;
            if(--nready <= 0)
                continue;
        }

        //轮询客户fd
        int i;
        for(i = 0; i <= maxi; ++i)
        {
            int fd = client[i];
            if(fd == -1)
                continue;
            //对每一个客户fd，查看是否在监听队列中
            if(FD_ISSET(client[i], &rset))
            {
                char recvbuf[1024] = {0};
                int ret = readline(fd, recvbuf, 1024);
                if(ret == -1)
                    ERR_EXIT("readline");
                else if(ret == 0)
                {
                    printf("client close\n");
                    close(fd);
                    client[i] = -1;
                    FD_CLR(fd, &allset);
                }

                printf("recv data : %s", recvbuf);
                writen(fd, recvbuf, strlen(recvbuf));
                if(--nready <= 0)
                    break;
            }
        }
    }
}



void do_poll(int listenfd)
{
    struct pollfd client[2048];
    int i;
    for(i = 0; i < 2048; ++i)
        client[i].fd = -1;

    client[0].fd = listenfd;
    client[0].events = POLLIN;
    int maxi = 0;
    int nready;

    while(1)
    {
        //poll
        nready = poll(client, maxi + 1, -1);
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
                    if(i > maxi)
                        maxi = i;
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
        for(i = 1; i <= maxi; ++i)
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
                    printf("client close\n");
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


void do_epoll(int listenfd)
{
    //创建epoll
    int epollfd = epoll_create(2048);
    if(epollfd == -1)
        ERR_EXIT("epoll_create");

    //添加listenfd
    struct epoll_event ev;
    ev.data.fd = listenfd;
    ev.events = EPOLLIN;
    if(epoll_ctl(epollfd, EPOLL_CTL_ADD, listenfd, &ev) == -1)
        ERR_EXIT("epoll_ctl");

    //创建数组
    struct epoll_event events[2048];
    int nready;

    while(1)
    {
        //wait
        nready = epoll_wait(epollfd, events, 2048, -1);
        if(nready == -1)
        {
            if(errno == EINTR)
                continue;
            ERR_EXIT("epoll_wait");
        }

        //遍历events数组
        int i;
        for(i = 0; i < nready; ++i)
        {
            int fd = events[i].data.fd;
            //如果listenfd
            if(fd == listenfd)
            {
                int peerfd = accept(listenfd, NULL, NULL);
                if(peerfd == -1)
                    ERR_EXIT("accept");

                //加入epoll
                struct epoll_event ev;
                ev.data.fd = peerfd;
                ev.events = EPOLLIN;
                if(epoll_ctl(epollfd, EPOLL_CTL_ADD, peerfd, &ev) == -1)
                    ERR_EXIT("epoll_ctl");
            }else//如果是普通fd
            {
                int peerfd = events[i].data.fd;
                char recvbuf[1024] = {0};
                int ret = readline(peerfd, recvbuf, 1024);
                if(ret == -1)
                    ERR_EXIT("readline");
                else if(ret == 0)
                {
                    //从epoll中删除
                    printf("client close\n");
                    struct epoll_event ev;
                    ev.data.fd = peerfd;
                    if(epoll_ctl(epollfd, EPOLL_CTL_DEL, peerfd, &ev) == -1)
                        ERR_EXIT("epoll_ctl");
                    close(peerfd);
                    continue;
                }
                printf("recv data %s", recvbuf);
                writen(peerfd, recvbuf, strlen(recvbuf));
            }
        }
    }
    //关闭epoll句柄
    close(epollfd);
}





















