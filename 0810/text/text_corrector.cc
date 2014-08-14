#include "text_corrector.h"
#include <echo/exception.h>
#include <stdio.h>
#include <sstream>
#include <fstream>
#include <iostream>
#include <algorithm>
#include <string>
#include <assert.h>
#include <string.h>

using namespace std;

TextCorrector::TextCorrector(const string &filename)
    :index_(26)
{
    //readCacheFile("cache.txt");
    readFile(filename);    
}

//读取文件，放入map对象词库Dic_中
void TextCorrector::readFile(const string &filename)
{
    //打开文件
    ifstream in;
    in.open(filename.c_str());
    if(!in)
        throw Exception("open file failed");
    //存储文件
    string line;
    while(getline(in, line))
        lines_.push_back(line);
    in.close();

    //建立词库
    for(vector<string>::size_type ix = 0; ix != lines_.size(); ++ix)
    {
        istringstream iss(lines_[ix]);
        string word;
        while(iss >> word )
        {
            //对一行的每个单词
            //大写转换成小写, 字符换成空格
            for(string::iterator it = word.begin(); it != word.end(); ++it)
            {
                if(isupper(*it))
                    tolower(*it);
                if(ispunct(*it))
                    *it = ' ';
            }
            string::iterator it = remove_if(word.begin(), word.end(), bind2nd(equal_to<char>(), ' '));
            word.erase(it, word.end());
            Word new_word;
            new_word.word_ = word;
            new_word.distance_ = 0;
            new_word.frequence_ = 0;

            Dic_.insert(make_pair(word, new_word));
        }
        in.clear();
    }
    //为词库建立索引
    //buildIndex();
}


string TextCorrector::textQuery(const string &word)
{
    //1.先进行单词转换,取出客户端发送时词尾的/r/n
    string tmp = word;
    while(*tmp.rbegin() == '\r' || *tmp.rbegin() == '\n')
    {
        tmp.resize(tmp.size() -1);
    }
    //2.先从缓存中查找

    //3.然后从词典中查找单词
    map<string, Word>::iterator loc;
    loc = Dic_.find(tmp);
    if(loc != Dic_.end())
    {
        return loc->first;
    }
    //找不到匹配单词，就执行查找策略
    else
    {
        map<string, Word> curDic = Dic_;
        for(loc = curDic.begin(); loc != curDic.end(); ++loc)
        {
            if(::abs(word.size() - loc->first.size()) > 3)
                continue;
            //if(!isIndex(tmp, loc->first))
             // continue;
            loc->second.distance_ = editDistance(tmp, loc->first);
            loc->second.is_set_ = true;
        }
        string result = searchFromFile(curDic);
        return result;
    }

}


//最短编辑距离
int TextCorrector::editDistance(const string &word, const string &des_word)
{
    assert(word.size() < 100 && des_word.size() < 100);
    int memo[100][100];
    memset(memo, 0, sizeof(memo));
    for(unsigned int i = 0; i <= word.size(); ++i)
        memo[i][0] = i;
    for(unsigned int i = 0; i <= des_word.size(); ++i)
        memo[0][i] = i;
    for(unsigned int i = 1; i <= word.size(); ++i)
    {
        for(unsigned int j = 1; j <= des_word.size(); ++j)
        {
            if(word[i-1] == des_word[j-1])
            {
                memo[i][j] = memo[i-1][j-1];
            }
            else
            {
                int ret ;
                ret = memo[i-1][j] < memo[i][j-1] ? memo[i-1][j] : memo[i][j-1];
                int min = (ret < memo[i-1][j-1] ? ret : memo[i-1][j-1]);
                min += 1;
                memo[i][j] = min;
            }
        }
    }
    return memo[word.size()][des_word.size()];
}

//建立优先级队列

//从词典中查找
string TextCorrector::searchFromFile(const map<string, Word> &Cur_dic)
{
    Word match_word;
    match_word.word_ = "";
    match_word.frequence_ = 0;
    match_word.distance_ = 3;
    map<string, Word>::const_iterator it;
    for(it = Cur_dic.begin(); it != Cur_dic.end(); ++it)
    {
        if(it->second.is_set_ && match_word < it->second)
            match_word = it->second;
    }
    return match_word.word_;
}

//建立索引，一个单词放在多个索引中，

void TextCorrector::buildIndex()
{
    map<string, Word>::iterator it;
    for(it = Dic_.begin(); it != Dic_.end(); ++it)
    {
        string word = it->first;
        for(size_t i = 0; i != word.size(); ++i) {
            cout << "A" << endl;
            cout << word << endl;
            index_[word[i] - 97].insert(word);
            cout << "B" << endl;
        }
    }
}


//判断单词是否在下标中???
/*
bool TextCorrector::isIndex(const string &usr_word, const string &des_word)
{
    string word = usr_word;
    for(size_t i = 0; i != word.size(); ++i)
    {
        set<string>::iterator it;
        set<string>::iterator endit = index_[word[i] - 97].end();
        it = index_[word[i] - 97].find(des_word);
        if(it != endit)
            return true;
    }   
    return false;
}
*/


