#include <iostream>
#include <string>
#include <vector>
#include <dirent.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
using namespace std;
#define ERR_EXIT(m) \
    do { \
        perror(m);\
        exit(EXIT_FAILURE);\
    }while(0)
int readFile(char *base_path);
int main(int argc, const char *argv[])
{
    DIR *dir;
    char base_path[1000];

    memset(base_path, '\0', sizeof(base_path));
    getcwd(base_path, 999);//获取当前路径
    printf("the current dir is :%s\n", base_path);
    
    memset(base_path, '\0', sizeof(base_path));
    strcpy(base_path, "./");
    readFile(base_path);

    return 0;
}

//这里readFile函数的参数传进要读取的文件路径
int readFile(char* base_path)
{
    DIR *dir;
    struct dirent *ptr;
    char base[1000];

    //opendir打开文件
    if((dir = opendir(base_path)) == NULL)
    {
        perror("open dir error...");
        exit(1);
    }   
    //读取文件/夹
    while((ptr = readdir(dir)) != NULL)
    {
        if(strcmp(ptr->d_name, ".") == 0 || strcmp(ptr->d_name, "..") == 0)
            continue;
        //file
        else if(ptr->d_type == 8)
        {
            //现在就是修改这里面，
            //进行文件的读取
           // printf("d_name:%s--%s\n", base_path, ptr->d_name);
            cout << "读取文件" << endl;
        }
        //link file
        else if(ptr->d_type == 10)
        {
            printf("d_name:%s---%s\n", base_path, ptr->d_name);
        }
        //dir
        else if(ptr->d_type == 4)
        {
            memset(base, '\0', sizeof(base));
            strcpy(base, base_path);
            strcat(base, "/");
            strcat(base, ptr->d_name);
            readFile(base);
        }
    }
    closedir(dir);
    return 1;
}












