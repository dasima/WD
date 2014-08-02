#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <dirent.h>
int main(int argc, const char *argv[])
{
    DIR *dir = opendir(".");
   // if(dir == NULL)
    //    ERR_EXIT("opendir");
    struct dirent *de;
    while((de = readdir(dir)) != NULL)
    {
        printf("%s\n", de -> d_name);
    }
    closedir(dir);
    return 0;
}
