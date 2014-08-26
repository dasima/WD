#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>

int main(int argc, const char *argv[])
{
    char block[65535];
    int in, out;
    int nread;

    in = open("out.txt", O_RDONLY);
    out = open("file.out", O_WRONLY | O_CREAT , S_IRUSR | S_IWUSR);
    while((nread = read(in, block, sizeof(block))) > 0)
    {
        printf("---%s----\n", block);
        write(out, block, nread);
    }
    return 0;
}
