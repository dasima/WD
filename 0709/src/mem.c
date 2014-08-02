#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void test()
{
    //c 
    int *ptr = malloc(1024);
}
//in test and main they are equal in memory allocation
int main(int argc, const char *argv[])
{
    int *pi = malloc(1024);
    char *s = malloc(1024);
    return 0;
}
