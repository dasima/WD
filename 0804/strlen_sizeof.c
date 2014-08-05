#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, const char *argv[])
{
    
    char c[9] = {'a', 'b'};
    printf("c---%d\n", strlen(c));//2
    printf("sizeof------%d\n", sizeof(c));//9
    char cc[] = {'a', 'b'};
    printf("cc strlen---%d\n", strlen(cc));//4
    printf("sizeof --- %d\n", sizeof(cc));//2
    char c1[] = "hello";
    printf("c---%d\n", strlen(c1));//5
    printf("sizeof------%d\n", sizeof(c1));//6
    char c2[9] = "hello";
    printf("c---%d\n", strlen(c2));//5
    printf("sizeof------%d\n", sizeof(c2));//9
    return 0;
}
