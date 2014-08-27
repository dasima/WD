#include <echo/rio.h>
#include <iostream>
#include <string>
#include <vector>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>

int main(int argc, const char *argv[])
{
    //read index_file
    int index = open("index.txt", O_RDONLY);
    lseek(index, 0, SEEK_CUR);
    char msg[100];
    read(index, msg, 3);
    printf("%d\n", (int)msg);
    /*
    char* nindex;
    char *s;
    printf("a\n");
    nindex = rio_readline(index, 10);
    printf("b\n");
    printf("%s\n", nindex);
    */
    //read_page.lib

    //cut
    
    return 0;
}
