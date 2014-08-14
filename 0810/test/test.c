#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, const char *argv[])
{
    int a[10], b[10];
    int i;
    
    for(i = 0; i < 10; ++i)
    {
        b[0] += a[i];
    }

    for(i = 0; i < 10; ++i)
    {
        printf("%d ", b[i]);
    }
    return 0;
}
