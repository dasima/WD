#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#define ERR_EXIT(m) \
    do { \
        perror(m);\
        exit(EXIT_FAILURE);\
    }while(0)
int main(int argc, const char *argv[])
{
    printf("hello");

    _exit(EXIT_SUCCESS);
    return 0;
}
