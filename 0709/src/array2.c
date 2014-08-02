#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define M 10
#define N 10  
//把数组用结构体包装起来,m n zhiding weidu 
typedef struct _Array {
    int m_;
    int n_;
    int A_[M][N];//指定最大个数
}Array;

void print(Array A, int m_, int n_)
{
    int i = 0, j = 0;
    for(i = 0; i != A.m_; ++i)
    {
        for(j = 0; j != A.n_; ++j)
            printf("%d ", A.A_[i][j]);
        printf("\n");
    }
}

int main(int argc, const char *argv[])
{
    int i, j;
    Array A;
    A.m_ = 2;//指定实际第一维的值
    A.n_ = 4;//指定实际第二维的值
    A.A_[2][4] ;
    for(i = 0; i != 2; ++i)
    {
        for(j = 0; j != 4; ++j)
            scanf("%d", &A.A_[i][j]);
    }
    print(A, 2, 4);
    return 0;
}
