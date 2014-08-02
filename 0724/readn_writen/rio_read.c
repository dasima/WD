#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#define ERR_EXIT(m)\
    do\
    {\
        perror(m);\
        exit(EXIT_FAILURE);\
    }while(0)

#define RIO_BUFFER 8192
typedef struct {
    int fd_;//要读取的fd
    int left_; // 代表缓冲区剩余的字节数
    char *bufPtr_; //缓冲区有效数据的起始位置
    char buffer_[RIO_BUFFER]; //缓冲区
}Rio_t;

void rio_init(Rio_t *rp, int fd)
{
    rp -> fd_ = fd;
    rp -> left_ = 0;
    rp -> bufPtr_ = rp -> buffer_;
}
//rio_read 应该提供和read相同的功能
//函数功能是把数据拷贝到缓冲区？？？
ssize_t rio_read(Rio_t *rp, char* sbuf, size_t n)
{
    size_t nread;
    //如果缓冲区里面没有数据，那么应该进行预读取
    //但是，不是每次调用rio_read都会进行预读取
    //使用while循环是因为？？？？
    //因为
    while(rp -> left_ <= 0)
    {
        nread = read(rp -> fd_, rp -> buffer_, sizeof(rp -> buffer_));
        if(nread == -1)
        {
            if(errno == EINTR)
                continue;
            return -1;
        }else if(nread == 0)
            return 0;

        rp -> left_ = nread;///????
        rp -> bufPtr_ = rp -> buffer_; //重置缓冲区的指针
    }

    //到达这里，buffer中一定存在数据
    int cnt = n;
    //如果缓冲区可提供的字节数小于用户要求的n
    //此时提供缓冲区中剩余的字节数
    if(rp -> left_ < n)
        cnt = rp -> left_;
    //执行数据拷贝
    memcpy(sbuf, rp -> bufPtr_, cnt);
    rp -> left_ -= cnt;//剩余字节数减少
    rp -> bufPtr_ += cnt;//指针后移

    return cnt;
}

ssize_t rio_readn(Rio_t *rp, void *sbuf, size_t n)
{
    size_t nleft = n;
    size_t nread;
    char* buf = sbuf;
    while(nleft > 0)
    {
        if((nread = rio_read(rp, buf, nleft)) == -1)
        {
            return -1;//这里不需要处理EINTR, 因为rio_read函数已经把数据读如缓冲区，这里不需要再进行系统调用？？？
        }else if(nread == 0)
            break;

        nleft -= nread;
        buf += nread;
    }
    return (n - nleft);
}

ssize_t rio_readline(Rio_t *rp, void *sbuf, size_t maxlen)
{
    size_t nread;
    char *buf = sbuf;
    char c;
    int i;
    //最多读取maxlen - 1 个字节，留一个位置给'\0'
    for(i = 0; i < maxlen - 1; ++i)
    {
        //这里也是读取一个字节
        //不过rio_read内部采用了Buffer机制
        //所以这里的效率没有降低
        if((nread = rio_read(rp, &c, 1) ) == -1)
        {
            return -1;
        }else if(nread == 0)
        {
            if(i == 0)//读取的第一个字符遇到EOF
                return 0;
            break;//这里可能已经读取了部分字节
        }

        *buf = c;//把字符放入缓冲区
        ++buf;

        if(c == '\n')
            break;     
    }
    *buf = '\0';
    return i;//获取成功读取的字节数，不包括最后的'\0'
}

ssize_t rio_writen(int fd, void *sbuf, size_t n)
{
    size_t nleft = n;
    size_t nwrite;
    char* buf = sbuf;
    while(nleft > 0)
    {
        if((nwrite = write(fd, buf, nleft)) <= 0)
        {
            if(errno == EINTR)
                nwrite = 0;
            else
                return -1;
        }
        nleft -= nwrite;
        buf += nwrite;
    }
    return n;
}

int main(int argc, const char *argv[])
{
    int fd = open("test.txt", O_RDONLY, 0666);
    if(fd == -1)
        ERR_EXIT("open");

    Rio_t rio;
    rio_init(&rio,fd);
    int ret;
    char buf[1024] = {0};
    while((ret = rio_readline(&rio, buf, 1024)) > 0)
        rio_writen(STDOUT_FILENO, buf, strlen(buf));
    /*
     //从终端进行输入输出
    Rio_t rio;
    rio_init(&rio, STDIN_FILENO);
    int ret;
    char buf[1024] = {0};
    while((ret = rio_readline(&rio, buf, 1024)) > 0)
        rio_writen(STDOUT_FILENO, buf, strlen(buf));
    */
    return 0;
}


