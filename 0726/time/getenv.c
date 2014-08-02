#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//获取某一项的全局变量
int main(int argc, const char *argv[])
{
    printf("%s\n", getenv("SHELL"));
    return 0;
}
