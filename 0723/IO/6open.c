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
     //O_WRONLY只写
     //O——CREAT文件不存在是创建
     //如果文件存在，则在文件尾进行追加
     //是运行后才在文件尾进行添加
    int fd = open("1.txt", O_WRONLY | O_CREAT | O_APPEND, 0666);
    if(fd == -1)
        ERR_EXIT("open");

    char buf[1024] = "shanghai";
    write(fd, buf, strlen(buf));

    close(fd);

    return 0;
}
