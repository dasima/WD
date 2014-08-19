#include "make_dict_cn.h"
#include <istream>
#include <fstream>
#include <vector>
#define LOGGER_LEVEL LL_WARN

using namespace CppJieba;
using namespace std;

//const char * const TEST_FILE = "../cppjieba/test/testdata/testlines.utf8";
const char * const TEST_FILE = "./a.txt";
const char * const JIEBA_DICT_FILE = "../cppjieba/dict/jieba.dict.utf8";
const char * const HMM_DICT_FILE = "../cppjieba/dict/hmm_model.utf8";

/*
 *实现中文切词功能
 *并建立中文词典
 */

MakeDictCn::MakeDictCn()
{
    makeDic();
}

void MakeDictCn::cut(const ISegment& seg, const char * const file_path)
{
    ifstream ifile(file_path);
    ofstream of("dic.txt");
    vector<string> words;
    string line;
    string res;
    string word;
    set<string> exclude_words;
    exclude_words.insert(",");
    while(getline(ifile, line))
    {
        if(!line.empty())
        {
            words.clear();
            seg.cut(line, words);
            //这里词库输出有问题，把vector容器中内容输出查看是否输出成功
            //for(vector<string>::iterator it = words.begin(); it != words.end(); ++it)
              //  cout << *it << endl;
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


void MakeDictCn::makeDic()
{
    //    printf("\e[32m%s\e[0m\n", "[demo] MixSegment"); // colorful
        MixSegment seg(JIEBA_DICT_FILE, HMM_DICT_FILE);
        cut(seg, TEST_FILE);
}



