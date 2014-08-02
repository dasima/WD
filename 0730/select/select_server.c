#include "network.h"
#include "socket.h"
#include <sys/select.h>
void do_select(int listenfd);
int main(int argc, const char *argv[])
{
    if(signal(SIGPIPE, SIG_IGN) == SIG_ERR)
        ERR_EXIT("signal");

    int listenfd = get_listen_fd();

    do_select(listenfd);

    close(listenfd);
    return 0;
}

void do_select(int listenfd)
{
    //准备一些初始化参数
    fd_set allset;//备份rset
    fd_set rset;
    int client[FD_SETSIZE];//保存已连接的客户fd
    int i;
    for(i = 0; i < FD_SETSIZE; ++i)
        client[i] = -1;
    int maxi = -1;//代表client中的最大下标
    int nread;
    int maxfd = listenfd;
    FD_ZERO(&allset);
    FD_ZERO(&rset);
    FD_SET(listenfd, &allset);

    while(1)
    {
        //初始化rset
        rset = allset;
        //执行select调用
        //rset既是输入参数，也是输出参数
        nread = select(maxfd + 1, &rset, NULL, NULL, NULL);
        if(nread == -1)
        {
            if(errno == EINTR)
                continue;
            ERR_EXIT("select");
        }else if(nread == 0)
            continue;
        
        //判断listenfd
        if(FD_ISSET(listenfd, &rset))
        {
            //accept
            int peerfd = accept(listenfd, NULL, NULL);
            if(peerfd == -1)
                ERR_EXIT("accept");
            //加入client同时处理client满的情况
            int i;
            for(i = 0; i < FD_SETSIZE; ++i)
            {
                if(client[i] == -1)
                {
                    client[i] = peerfd;
                    if(i > maxi)
                        maxi = i;//最大下标需要更新
                    break;
                }
            }
            if(i == FD_SETSIZE)
            {
                fprintf(stderr, "too many clients\n");
                exit(EXIT_FAILURE);
            }
            //加入allset中,(进行修改的地方都是allset)
            FD_SET(peerfd, &allset);
            if(peerfd > maxfd)
                maxfd = peerfd;//更新maxfd
            if(--nread <= 0)
                continue;
        }

        //轮询客户fd
        int i;
        for(i = 0; i <= maxi; ++i)
        {
            if(FD_ISSET(client[i], &rset))
            {
                char recvbuf[1024] = {0};
                int fd = client[i];
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

                printf("recv data :%s", recvbuf);
                writen(fd, recvbuf, strlen(recvbuf));

                if(--nread <= 0)
                    break;
            }
        }
    }
}
