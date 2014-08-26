#include "../include/document.h"
#include <fstream>
#include <echo/exception.h>
#include <dirent.h>
#include <stdlib.h>
#include <string>
#include <cstring>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#define ERR_EXIT(m) \
    do { \
        perror(m);\
        exit(EXIT_FAILURE);\
    }while(0)
using namespace std;


//把txt格式的文件转化成doc格式
void Document::txtToDoc(const string &filename)
{
    ifstream in;
    in.open(filename.c_str());
    if(!in)
        throw Exception("file");
   // cout << filename << endl;
    string doc = "";
    //string url = "";
    string title = "";
    string content = "";

    string line;
    int i = 1;
    while(getline(in, line))
    {
        line.resize(line.size() - 1);
        if(i == 1)
        {
            title = line;
            i = 0;
        }
        else
        {
            content += line;
        }

    }

    doc = string("<doc>\n") + 
        "   <url>www.dasima.com</url>\n" +
        "   <title>" + title + "</title>\n" +
        "   <content>\n" +
        content +
        "   </content>\n"+ 
        "</doc>\n";
    Vec_.push_back(doc);//把每一篇转化后的文档放入vector中
}

//遍历读取多个文件夹中的文件
int Document::readFile(char *base_path)
{
    DIR *dir;
    struct dirent *ptr;
    char base[1000];

    //打开路径
    if((dir = opendir(base_path)) == NULL)
        ERR_EXIT("open dir error.");
    //这里需要更新路径
    chdir(base_path);
    //读取当前路径下的文件
    while((ptr = readdir(dir)) != NULL)
    {
        if(strcmp(ptr->d_name, ".") == 0 || strcmp(ptr->d_name, "..") == 0)
        {
            continue;
        }
        //file
        else if(ptr->d_type == 8)
        {
            //如果是文件，则执行文件操作
            //cout << "read file " << ptr->d_name << endl;
            //这里使用绝对路径--错误
           // char str[1000];
            //getcwd(str, 999);
            //txtToDoc(string(str) + ptr->d_name);
            txtToDoc(ptr->d_name);
        }
        //link file
        else if(ptr->d_type == 10)
        {
            cout << "link file" << endl;
        }
        //dir
        else if(ptr->d_type == 4)
        {
            //打印当前目录
            //cout << "dir" << ptr->d_name << endl;

            //如果是目录，就更新目录到子目录
            memset(base, '\0', sizeof(base));
            strcpy(base, base_path);
            strcat(base, "/");
            strcat(base, ptr->d_name);
            //这里如果是子目录，就递归读取
            readFile(base);
        }
    }
    //子目录读取完之后需要回到父目录
    chdir("..");
    closedir(dir);
}

//把文档内容以指定格式存入一个库文件中
void Document::buildLib(const string &filename, const string &filename2)
{
    //c++ 的IO组件实现建立静态库(该实现只有一个参数)
    /*
    ofstream of;
    //of.open(filename.c_str(), ofstream::app);
    of.open(filename.c_str());
    if(!of)
        throw Exception("open pagelib failed");
    vector<string>::iterator vit = Vec_.begin();
    for(; vit != Vec_.end(); ++vit)
    {
        //cout << i << " " << of.tellp();
        //of << i << " " << of.tellp();
        of << *vit ;//写入文件内容
        //of << (*vit).size() << endl;//统计文件大小
    }
    */

    //linux的open、read、write实现建立静态库和索引表
    int fd = open(filename.c_str(), O_WRONLY || O_APPEND);
    int fd2 = open(filename2.c_str(), O_WRONLY || O_APPEND);
    char *buf;
    vector<string>::iterator vit = Vec_.begin();
    int offset = 0;
    int i = 1;
    for(; vit != Vec_.end(); ++vit)
    {
        //cout << ((*vit).size()) << endl;
        write(fd, (*vit).c_str(), (*vit).size());

        //cout << " --offset --" << offset << " " ; 
        //cout << to_string(i) << " " ;//c++11
        string s = to_string(i) + " " + to_string(offset) + " " + to_string((*vit).size()) + "\n";
        //cout << s.size() << " " ;
        write(fd2, s.c_str(), s.size());
        offset = lseek(fd, 0, SEEK_CUR);
        ++i;
    }

}

void Document::buildIndex(const string &filename)
{
    size_t i = 1;//这里i用来统计文件数量
    ofstream of;
    //of.open(filename.c_str(), ofstream::app);
    of.open(filename.c_str());
    if(!of)
        throw Exception("open pagelib failed");
    vector<string>::iterator vit = Vec_.begin();
    for(; vit != Vec_.end(); ++vit)
    {
        //想索引文件中写入id、偏移量、文件大小
        of << i << " " ;
        of << of.tellp() << " ";//tellp是c++中的当前字符的位置
        of << (*vit).size() << endl;
        ++i;
    }
    cout << i << endl;
}

