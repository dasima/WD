#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, const char *argv[])
{
    int fd = open("test.txt", O_RDONLY, 0666);
    if(fd == -1)
        ERR_EXIT("open");

    char buf[1024] = {0};
    read(fd, buf, 5);
    printf("buf ---- %s\n", buf);

    off_t len = lseek(fd, 0, SEEK_CUR);
    printf("len ---- %d", (int)len);
    return 0;
}
