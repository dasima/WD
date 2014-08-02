#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/*
 *本例演示创建多进程
 */
int main(int argc, const char *argv[])
{
    fork();
    fork();
    fork();

    printf("hell\n");
    //输出结果将是8个hello
    return 0;
}
