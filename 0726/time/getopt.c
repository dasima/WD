#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define ERR_EXIT(m) \
    do { \
        perror(m);\
        exit(EXIT_FAILURE);\
    }while(0)
//获取命令行选项
int main(int argc, char* const argv[])
{
    int opt;
    while(1)
    {
        opt = getopt(argc, argv, "nt:");
        if(opt == '?')
            exit(EXIT_FAILURE);
        if(opt == -1)
            break;
    }
    switch(opt)
    {
        case 't' :
            printf("-t\n");
            break;
        case 'n' :
            printf("-n%d\n", atoi(optarg));
            break;
    }
    return 0;
}
