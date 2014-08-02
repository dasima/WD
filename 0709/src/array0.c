#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void print(int* A)
{
    printf("int function print, the length if A is %d\n", sizeof(A)/sizeof(A[0]));
}   

int main(int argc, const char *argv[])
{
    int B[9];
    int (*arr)[9] = &B;

    int A[9] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    printf("int main the length of A is %d\n", sizeof(A)/sizeof(A[0]));
    print(A);
    return 0;
}
