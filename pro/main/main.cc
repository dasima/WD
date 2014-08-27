#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include <set>
#include "../lib/cppjieba/src/MixSegment.hpp"
#define LOGGER_LEVEL LL_WARN

using namespace CppJieba;
using namespace std;

string TEST_FILE = "in.txt";
const char * const JIEBA_DICT_FILE = "../include/cppjieba/dict/jieba.dict.utf8";
const char * const HMM_DICT_FILE = "../include/cppjieba/dict/hmm_model.utf8";

//切分中文单词
void cut(const ISegment& seg, string file_path)
{
    cout << "c" << endl;
    ifstream ifile(file_path.c_str());
    vector<string> words;
    string line;//存放从文本读取的一行数据
    string res;//
    string word;//从一行数据中读取一个单词
    while(getline(ifile, line))
    {        
        if(!line.empty())
        {
            words.clear();
            seg.cut(line, words);
            join(words.begin(), words.end(), res, " ");

            istringstream iss(res);
            while(iss >> word)
            {
                cout << word << endl;
            }
        }
    }
}


void makeDic()
{
        MixSegment seg(JIEBA_DICT_FILE, HMM_DICT_FILE);
        cout << "b" << endl;
        cut(seg, TEST_FILE);
}

int main(int argc, const char *argv[])
{
    cout << "a" << endl;
    makeDic();
    return 0;
}
