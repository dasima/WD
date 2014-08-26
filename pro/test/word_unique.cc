#include "word_unique.h"
#include <echo/exception.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sstream>
#include <fstream>
#include <iostream>
#include <cstdio>
#include <string>
#include "../lib/cppjieba/src/MixSegment.hpp"
using namespace std;
using namespace CppJieba;

const char * const JIEBA_DICT_FILE = "../lib/cppjieba/dict/jieba.dict.utf8";
const char * const HMM_DICT_FILE = "../lib/cppjieba/dict/hmm_model.utf8";


WordUnique::WordUnique()
{
    //getDoc(); 
}

void WordUnique::getDoc()
{
    ifstream in;
    in.open("../data/index.txt");
    if(!in)
        throw Exception("open file failed");
    //int fd = open("../data/index.txt", O_RDONLY);

    int fd2 = open("../data/page.lib", O_RDONLY);
    if(fd2 == -1)
    {
        perror("open failed");
        return;
    }
    char buf[100000];
    int fsize;
    int offset;
    string line;
    if(getline(in, line))
    {
        //获取偏移量和文档大小
        istringstream iss(line);
        iss >> fsize;
        iss >> offset;
        //cout << offset << endl;
        iss >> fsize;
        cout << fsize << endl;
        //cout << sizeof(fsize) << endl;

        //获取一个文本内容
        //Rio Rio_(fd2);//这里我的rio中readn函数参数为const类型，是不对的
        lseek(fd2, offset, SEEK_SET);
        int ret;
        if(read(fd2, buf, fsize))
        {
            //printf("%s", buf);

            //获取一片文档中的content内容
            string content = string(buf);
            size_t pos1, pos2;
            pos1 = content.find("<content>") + 9;
            pos2 = content.find("</content>");
            string con = content.substr(pos1, pos2 - pos1);
            //cout << con << endl;
            //cout << pos1 <<  " " << pos2 << endl;
           
            Vec_.push_back(con);
            //对每一个文本进行处理
            //这里可以函数返回值为string类型的con,从而不进行函数调用
            //do(con);
        }
    }
    vector<string>::iterator vit = Vec_.begin();
    string s = *vit;
    makeCut(s);
}

//这里需要每次传给makeCut一个字符串参数
void makeCut(const string &path)
{
    MixSegment seg(JIEBA_DICT_FILE, HMM_DICT_FILE);
    cutWord(seg, path);
}

void WordUnique::cutWord(const ISegment &seg, const char * const filename)
{
    char *file = filename;
    ifstream in(filename);
    if(!in)
        throw Exception("open fail");
    vector<string> words;
    string line;
    string res;
    while(getline(in, line))
    {
        if(!line.empty())
        {
            words.clear();
            seg.cut(line, words);
            join(words.begin(), words.end(), res, " ");
            cout << res << endl;
        }
    }
}


