#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int swap(int ********a, int ********b)
{
    int ********temp = *a;
    *a = *b;
    *b = *temp;
}
int main(int argc, const char *argv[])
{
    int i = 10;
    int j = 9;
    printf("i = %d  j = %d\n", i, j);
    int *******a = &i;
    int *******b = &j;
    swap(&a, &b);
    printf("i = %d  j = %d\n", i, j);
    return 0;
}
