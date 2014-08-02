#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <fcntl.h>
#define ERR_EXIT(m)\
    do\
    {\
      perror(m);\
      exit(EXIT_FAILURE);\
    }while(0)
ssize_t readn(int fd, void *sbuf, size_t n);
ssize_t writen(int fd, void *sbuf, size_t n);
int main(int argc, const char *argv[])
{
    int fd = open("test.txt", O_RDONLY);
    if(fd == -1)
        ERR_EXIT("open");

    char buf[1024] = {0};
    int ret;
    while((ret = readn(fd, buf, 5)) > 0)
    {
        writen(STDOUT_FILENO, buf, ret);
    }
    
    return 0;
}
/*
 *这里readn返回值有三种：
 *
 *1，如果没有遇到EOF，就读取n个字节，
 *遇到EOF，就读取到EOF为止的字节数
 *
 *成功时返回值是返回的字节数
 *如果是字节数小于n，一定是遇到了EOF
 *2，如果出错，则返回-1，这里的错误不包含EINTR
 *3，如果一开始就遇到EOF，返回0
 *
 */
ssize_t readn(int fd, void *sbuf, size_t n)
{
    size_t nleft = n;//表示还要读取的字节数
    ssize_t nread;//read读取的返回值
    char *buf = sbuf;

    while(nleft > 0)
    {
        nread = read(fd, buf, nleft);
        if(nread == -1)
        {
            if(nread == EINTR)//中断引起的系统调用不成功，
                nread = 0;//这时需要再次读取，重新进行系统调用
            else
                return -1;
        }else if(nread == 0)//EOF
            break;//遇到文件结束，跳出循环

        nleft -= nread;
        buf += nread;
    }
    return (n - nleft);//返回读取的字节数
}
/*
 *这里writen必须写满字节数
 *少于n属于错误
 *
 *write返回值有两种：
 *n代表成功读取的字节数
 *-1代表失败
 */
ssize_t writen(int fd, void *sbuf, size_t n)
{
    size_t nleft = n;
    ssize_t nwrite;
    char *buf = sbuf;

    while(nleft > 0)
    {
        nwrite = write(fd, buf, nleft);
        //nwrite = 0； 也属于错误
        if(nwrite <= 0)
        {
            if(errno == EINTR)
                nwrite = 0;
            else
                return -1;
        }
        nleft -= nwrite;
        buf += nwrite;
    }
    return n;//这里必须是n，而不能是n - nleft
}
