#include <stdio.h>
#include <stdlib.h>
#include <string.h>
extern char **environ;

#define ERR_EXIT(m) \
    do { \
        perror(m);\
        exit(EXIT_FAILURE);\
    }while(0)
//获取环境变量
int main(int argc, const char *argv[])
{
    int i;
    for(i = 0; environ[i] != NULL; ++i)
        printf("%d: %s\n", i, environ[i]);

    return 0;
}
