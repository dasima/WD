#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void test(char* s)
{
    malloc(1024);//值传递，传递的是副本，这里会分配错误
}

void test_1(char** s)//
{
    malloc(1024);
}

char* test_2(char* s)
{
    malloc(1024);
    return s;
}
int int main(int argc, const char *argv[])
{
    char* s = NULL;
    test_1(s);
    return 0;
}
