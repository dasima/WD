#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void test0(char* s)
{
    s = malloc(1024);
}

void test(char** s)
{
    *s = malloc(1024);
}   

char* test2(char* s)
{
    s = malloc(1024);
    return s;
}
int main(int argc, const char *argv[])
{
    char* s = NULL;
    test(&s);
    s = test2(s);
    return 0;
}
