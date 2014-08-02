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
    FILE *fp = fopen("test.txt", "r");
    if(fp == NULL)
    {
        fprintf(stderr, "open file failed\n");
        exit(EXIT_FAILURE);
    }
    
    char buf[1024] = {0};
    fgets(buf, 1024, fp);
    printf("read ---%s\n", buf);

    fclose(fp);

    return 0;
}
