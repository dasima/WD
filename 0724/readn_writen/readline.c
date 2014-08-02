#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <fcntl.h>
#include <unistd.h>

//没有结束宏定义前每次换行都要有'\'
//13行这里不能少了分号；
//15行注意末尾没有分号;
#define ERR_EXIT(m)\
    do\
    {\
        perror(m);\
        exit(EXIT_FAILURE);\
    }while(0)
ssize_t readline(int fd, void *sbuf, size_t maxlen);
int main(int argc, const char *argv[])
{
    int fd = open("test.txt", O_RDONLY);
    if(fd == -1)
    {
        ERR_EXIT("open");
    }
    int ret;
    char buf[1024];
    while((ret = readline(fd, buf, 1024)) )
    {
        printf("ret = %d, buf --- %s\n", ret, buf);
    }
    
    return 0;
}
/*
 *效率低下
 *参数需指定为maxlen， 但是最多读取内容为maxlen - 1
 *z最后一个位置留给'\0'
 *
 *maxlen足够大的情况下，buf的最终内容为 XXX \n\0
 *
 */
ssize_t readline(int fd, void *sbuf, size_t maxlen)
{
    char *buf = sbuf;//记录缓冲区当前位置
    ssize_t nread;
    size_t nleft = maxlen - 1;//留一个字节存放'\0'
    char c;
    while(nleft > 0)
    {
        if((nread = read(fd, &c, 1)) == -1)
        {
            if(errno == EINTR)
                continue;
            return -1;
        }else if(nread == 0)
            break;
        //读取正常
        *buf = c;
        ++buf;
        --nleft;

        if(c == '\n')
            break;
    }
    *buf = '\0';
    return (maxlen -nleft -1);//前面留了一个字节给'\0'，所以这里需要再减去一个1
}
