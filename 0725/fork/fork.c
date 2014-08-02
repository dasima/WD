#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>

int main(int argc, const char *argv[])
{
    pid_t pid;
    char *message;
    int n;

    printf("fork start\n");
    pid = fork();
    switch(pid)
    {
        case -1 :
            perror("fork failed");
            exit(1);
        case 0 :
            message = "child";
            n = 5;
            break;
        default :
            message = "parent";
            n = 3;
            break;

    }
    for(; n > 0; --n)
    {
        puts(message);
        sleep(1);
    }
    
    return 0;
}
