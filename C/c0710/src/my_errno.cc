#include <iostream>
#include <string>
#include <vector>
#include <sys/types.h>
#include <sys/socket.h>
#include <cstdio>
#include <cstdlib>
using namespace std;
//使用宏可减少代码函数
#define ERR_EXIT(m)\
    do\
    {\
      perror(m);\
        exit(EXIT_FAILURE);\
    }while(0)
int main(int argc, const char *argv[])
{
    int fd = socket(AF_INET, SOCK_STREAM, 0);
    if(fd == -1)
    {
        ERR_EXIT("socket");
     //   perror("socket:");
       // exit(EXIT_FAILURE);
    }
    return 0;
}
