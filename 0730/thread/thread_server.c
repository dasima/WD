#include "network.h"
#include "pthread.h"
#include <netinet/in.h>


void do_service(int peerfd);
void *thread_func(void*);
int main(int argc, const char *argv[])
{
    if(signal(SIGPIPE, SIG_IGN) == SIG_ERR)
        ERR_EXIT("signal");

    int listenfd = get_listen_fd();

    while(1)
    {
        int peerfd = accept(listenfd, NULL, NULL);;
        if(peerfd == -1)
            ERR_EXIT("accept");
        //没接受一个请求，就创建一个新的线程
        int *pfd = (int*)malloc(sizeof(int));
        if(pfd == NULL)
            ERR_EXIT("malloc");
        *pfd = peerfd;
        pthread_t tid;

        if(pthread_create(&tid, NULL, thread_func, pfd))
            free(pfd);//确保内存不泄露
    }
    close(listenfd);
    return 0;
}

void *thread_func(void* arg)
{
    int *pfd = (int*)arg;
    int peerfd = *pfd;
    free(pfd);
    pthread_detach(pthread_self());//把自己设为分离状态

    do_service(peerfd);
    close(peerfd);
}

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
        writen(peerfd, recvbuf, strlen(recvbuf));
    }
}

