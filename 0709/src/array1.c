#include <stdio.h>
#include <stdlib.h>
#include <string.h>
void print(int (*A)[4], int m, int n)
{//二维数组传参问题
    int i, j;
    for(i = 0; i != m; ++i)
    {
        for(j = 0; j != n; ++j)
            printf("%d ", A[i][j]);
        printf("\n");
    }
}
int main(int argc, const char *argv[])
{
    int a[2][4] = {1, 2, 3, 4, 5, 6};
    print(a, 2, 4);
    return 0;
}
