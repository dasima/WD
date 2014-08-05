#ifndef _READ_WRITE_H_
#define _READ_WRITE_H_ 

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <errno.h>
#include <signal.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define ERR_EXIT(m)\
    do\
    {\
      perror(m);\
        exit(EXIT_FAILURE);\
    }while(0)

ssize_t readn(int fd, void* usrbuf, size_t n)
{
    size_t nleft = n;//表示还需要读取的字节数
    ssize_t nread;
    char* buf = (char*)usrbuf;//控制read函数存放的位置

    while(nleft > 0)
    {
        if((nread = read(fd, buf, nleft)) == -1)
        {
            if(errno == EINTR)
                nread = 0;//中断需要再次读取
            return -1;//ERROR
        }else if(nread == 0)//EOF
            break;

        nleft -= nread;
        buf += nread;//存放数据的位置后移nread字节
    }
    return (n - nleft);
}

ssize_t writen(int fd, void* usrbuf, size_t n)
{
    char *buf = (char*)usrbuf;
    size_t nleft = n;
    ssize_t nwrite;

    while(nleft > 0)
    {
        //nwrite = 0 也属于错误
        if((nwrite = write(fd, buf, nleft)) <= 0)
        {
            if(errno == EINTR)
                nwrite = 0;
            return -1;//-1 和 0都属于写入失败
        }

        nleft -= nwrite;
        buf += nwrite;
    }
    return n;//这里必须是n，不是n-nleft
}

//recv_peek选项完成一次正确的读取过程
ssize_t recv_peek(int sockfd, void* buf, size_t len)
{
    int nread;
    while(1)
    {
        //这个过程只成功调用一次
        nread = recv(sockfd, buf, len, MSG_PEEK);
        //被终端则继续读取
        if(nread < 0 && errno == EINTR)
            continue;
        if(nread < 0)
            return -1;
        break;
    }
    return nread;
}

ssize_t readline(int fd, void* usrbuf, size_t maxline)
{
    int nread;//一次IO读取的数量
    int nleft = maxline - 1;//还剩余的字节数
    char* buf = (char *)usrbuf;//存放数据的指针的位置
    int ret;//readn的返回值
    int total = 0;//目前总共读取的字节数

    while(nleft > 0)
    {
        //这次调用是先预览数据，
        //并没有真正把数据从缓冲区中取走
        ret = recv_peek(fd, buf, nleft);
        //这里读取字节不够不是错误，只是成功执行后，读取字节数没达到预想目标
        if(ret <= 0)
            return ret;

        nread = ret;
        int i;
        for(i = 0; i < nread; ++i)
        {
            //这里开始正式读取，遇到换行就读取
            if(buf[i] == '\n')
            {
                ret = readn(fd, buf, i+1);
                if(ret != i+1)
                    return -1;
                total += ret;
                buf += ret;
                *buf = 0;
                return total;//返回的长度包含了‘\n'
            }
        }
        //如果没有发现\n，就全部接收已读取数据
        ret = readn(fd, buf, nread);
        if(ret != nread)
            return -1;
        nleft -= nread;
        total += nread;
        buf += nread;
    }
    *buf = 0;
    return maxline - 1;
}


#endif  /*_READ_WRITE_H_*/
