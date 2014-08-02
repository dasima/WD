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
    char buf1[1024] = {0};
    fd1 = open("tes.txt", O_WRONLY | O_CREAT, 0666);
    write(fd1, "AAAAA", 5);
    printf("buf1 --- %s\n", buf1);

    close(fd1);
    return 0;
}
