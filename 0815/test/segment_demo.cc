#include <iostream>
#include <istream>
#include <fstream>
#define LOGGER_LEVEL LL_WARN
#include "../cppjieba/src/MixSegment.hpp"

using namespace CppJieba;

const char * const TEST_FILE = "../cppjieba/test/testdata/testlines.utf8";
//const char * const TEST_FILE = "./a.txt";
const char * const JIEBA_DICT_FILE = "../cppjieba/dict/jieba.dict.utf8";
const char * const HMM_DICT_FILE = "../cppjieba/dict/hmm_model.utf8";

/*
 *实现中文切词功能
 *并建立中文词典
 */
void cut(const ISegment& seg, const char * const filePath)
{
    ifstream ifile(filePath);
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
            join(words.begin(), words.end(), res, " ");
            //cout<< res << endl;
            //这里res没有去掉逗号

            istringstream iss(res);
            while(iss >> word)
            {
                /*
                for(string::size_type ix = 0; ix != word.size(); ++ix)
                {
                    if(ispunct(word[ix]))
                        word[ix] = ' ';
                }
                */
                if(!exclude_words.count(word))
                    of << word << endl;
            }
        }
    }
}


int main(int argc, char ** argv)
{
    {
    //    printf("\e[32m%s\e[0m\n", "[demo] MixSegment"); // colorful
        MixSegment seg(JIEBA_DICT_FILE, HMM_DICT_FILE);
        cut(seg, TEST_FILE);
    }
    return EXIT_SUCCESS;
}
