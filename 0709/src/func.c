#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//函数指针问题

void test()
{
    printf("test\n");
}

void test2()
{
    printf("test2\n");
}

int main(int argc, const char *argv[])
{
    void(*func)(void);
    func = test;
    func();
    func = test2;
    func();
    return 0;
}
