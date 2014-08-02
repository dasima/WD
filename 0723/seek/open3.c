#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#define ERR_EXIT(m)\
    do\
    {\
        perror(m);\
        exit(EXIT_FAILURE);\
    }while(0)

int main(int argc, const char *argv[])
{
    int fd1;
    //文件不存在则创建，存在则清空后在文件中添加元素
    fd1 = open("tes.txt", O_WRONLY | O_CREAT | O_TRUNC, 0666);
    write(fd1, "BBBBB", 5);

    close(fd1);
    return 0;
}
