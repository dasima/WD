#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//二维数组的分配与释放
int main(int argc, const char *argv[])
{
    int *ptr = (int*)malloc(9 * sizeof(int));
    free(ptr);

    //3*4
    int **arr = (int **)malloc(3 * sizeof(int*));
    int i;
    for(i = 0; i != 3; ++i)
        arr[i] = (int*)malloc(4 * sizeof(int));
    for(i = 0; i != 3; ++i)
        free(arr[i]);
    free(arr);
    return 0;
}
