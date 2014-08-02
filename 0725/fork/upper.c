#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int main(int argc, const char *argv[])
{
    int ch;
    while((ch = getchar() ) != EOF)
        putchar(toupper(ch));
    return 0;
}
