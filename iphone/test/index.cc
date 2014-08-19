#include "index.h"
#include <iostream>

using namespace std;

void Index::buildIndex(const map<string, Word> &dic)
{
    map<string, Word>::iterator mit;
    map<string, Word> words[26];
    for(mit = dic.begin(); mit != dic.end(); ++mit)
    {
        string word = mit->first;
        char index_c = *(word.begin());
        int index = (index_c - 97);
        if(index >= 0 && index <= 25)
        {
            words[index][word] = mit->second;
            Index_[index_c] = words[index];
        }
    }
    map<uint32_t, set<Word> >::iteraotr msit = Index_.begin();
    for(; msit != Index_.end(); ++msit)
    {
        cout << msit->first << " " << (msit->second).Word_ << endl;
    }

}



