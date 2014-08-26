#include <iostream>
#include <string>
#include <vector>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
using namespace std;
#define ERR_EXIT(m) \
    do { \
        perror(m);\
        exit(EXIT_FAILURE);\
    }while(0)
/*
 *查看文件信息
 */
int main(int argc, const char *argv[])
{
    struct stat buf;
    if(stat(argv[1], &buf))
        ERR_EXIT("argv[1]");

    cout << "st_dev " << buf.st_dev << endl;
    cout << "st_mode " << buf.st_mode << endl;
    cout << "st_ino " <<  buf.st_ino << endl;

    return 0;
}
