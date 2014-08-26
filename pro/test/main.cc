#include <echo/exception.h>
#include <istream>
#include <fstream>
#include <vector>
#include <set>
#include "MixSegment.hpp"
#include <word_unique.h>
#define LOGGER_LEVEL LL_WARN

using namespace CppJieba;
using namespace std;

const char * const TEST_FILE = "in.txt";
const char * const JIEBA_DICT_FILE = "../include/cppjieba/dict/jieba.dict.utf8";
const char * const HMM_DICT_FILE = "../include/cppjieba/dict/hmm_model.utf8";

//切分中文单词
void cut(const ISegment& seg, const char * const file_path)
{
    ifstream ifile(file_path);
    ofstream of("out.txt");
    vector<string> words;
    string line;//存放从文本读取的一行数据
    string res;//
    string word;//从一行数据中读取一个单词
    set<string> exclude_words;
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
                if(!exclude_words.count(word))
                    of << word << endl;
            }
        }
    }
}


void makeDic()
{
        MixSegment seg(JIEBA_DICT_FILE, HMM_DICT_FILE);
        cut(seg, TEST_FILE);
}

int main(int argc, const char *argv[])
{
    WordUnique wu;
  //  makeDic();
    return 0;
}
