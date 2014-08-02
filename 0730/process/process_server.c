#include "network.h"
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
        //模拟数据处理过程
        printf("recv data :%s", recvbuf);
        writen(peerfd, recvbuf, sizeof(recvbuf));
    }
}

void handler(int sig)
{
    while(waitpid(-1, NULL, WNOHANG) > 0)
        ;
    return ;
}

int main(int argc, const char *argv[])
{
    if(signal(SIGPIPE, SIG_IGN) == SIG_ERR)
        ERR_EXIT("signal");
    if(signal(SIGCHLD, handler) == SIG_ERR)
        ERR_EXIT("signal");

    int listenfd = get_listen_fd();

    while(1)
    {
        struct sockaddr_in peeraddr;
        memset(&peeraddr, 0, sizeof peeraddr);
        socklen_t len = sizeof peeraddr;
        int peerfd = accept(listenfd, (struct sockaddr*)&peeraddr, &len);
        if(peerfd == -1)
            ERR_EXIT("accept");
        pid_t pid;
        if((pid = fork()) < 0)
            ERR_EXIT("fork");
        else if(pid == 0)
        {
            close(listenfd);//子进程必须关闭listenfd
            do_service(peerfd);
            exit(EXIT_SUCCESS);
        }

        close(peerfd);//这里必须关闭peerfd，否则导致资源耗尽
    }
    close(listenfd);
    return 0;
}

