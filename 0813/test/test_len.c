#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int getLenOfUTF8(unsigned char c)
{
    int cnt = 0;
    while(c & (1 << (7 - cnt)))
    {
        ++cnt;
    }
    return cnt;
}

int main(int argc, const char *argv[])
{
    unsigned char c = 's';
    unsigned int a = getLenOfUTF8(c);
    printf("%u\n", a);
    return 0;
}
