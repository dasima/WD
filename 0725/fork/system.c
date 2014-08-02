#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, const char *argv[])
{
    printf("running ps as system\n");

    system("ps aux");
    printf("Done\n");
    return 0;
}
