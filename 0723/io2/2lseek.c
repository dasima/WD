#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <errno.h>
#include <signal.h>
#define ERR_EXIT(m)\
    do\
    {\
        perror(m);\
        exit(EXIT_FAILURE);\
    }while(0)


int main(int argc, const char *argv[])
{
    int fd = open("test.txt", O_RDONLY, 0666);
    if(fd == -1)
        ERR_EXIT("open");

    char buf[1024] = {0};
    read(fd, buf, 5);
    printf("buf ---- %s\n", buf);

    off_t len = lseek(fd, 6, SEEK_CUR);//上面read后偏移量已经移到hello后空格处，
    //此处lseek中6是从上面空格处又向后偏移六位，
    //即到world后面空格处
    //所以，后面的printf语句，buf输出的是（换行符+4字节字符， 其中换行符占一个字节）
    printf("offset --- %d\n", (int)len);
    
    memset(buf, 0, strlen(buf));
    read(fd, buf, 5);
    printf("buf --- %s\n", buf);

    len = lseek(fd, 0, SEEK_CUR);
    printf("offset --- %d\n", (int)len);

    close(fd);

    return 0;
}
