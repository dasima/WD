#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define ERR_EXIT(m) \
    do { \
        perror(m);\
        exit(EXIT_FAILURE);\
    }while(0)

void test1()
{
    printf("test1\n");
}
void test2()
{
    printf("test2\n");
}
void test3()
{
    printf("test3\n");
}
int main(int argc, const char *argv[])
{
    //atexit用于向系统注册一些函数，当进程退出是执行这些函数
    atexit(test1);
    atexit(test2);
    atexit(test3);
    
    exit(EXIT_FAILURE);//exit会处理atexit注册的函数

    //_exit(EXIT_FAILURE);//不会处理atexit注册的函数
   // return 0;
}
