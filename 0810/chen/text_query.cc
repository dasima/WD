#include "text_query.h"
#include <stdio.h>
#include <echo/Exception.h>
#include <fstream>
#include <sstream>
#include <functional>
#include <algorithm>
#include <string.h>
#include <string>
#include <vector>
using namespace std;

TextQuery::TextQuery(const string &filename)
{
    readFile(filename);
}

void TextQuery::readFile(const string &filename)
{
    //打开读取文件
    ifstream in;
    in.open(filename.c_str());
    if(!in)
        throw Exception("open file fail");
    string line;
    while(getline(in, line))
    {
        lines_.push_back(line);        
    }
    in.close();

    for(vector<string>::size_type ix = 0;
            ix != lines_.size(); ++ix)
    {
        istringstream iss(lines_[ix]);
        string word;
        //对每一行输入的单词
        while(iss >> word)
        {
            //对输入的这个单词，大写换小写，标点换空格
            for(string::iterator it = word.begin(); it != word.end(); ++it) {
                if (isupper(*it))
                    tolower(*it);
                if (ispunct(*it))
                    *it = ' ';
            }
            //遍历word，第三个参数为真，就移除该字符
            string::iterator new_end = remove_if(word.begin(), word.end(), bind2nd(equal_to<char>(), ' '));
            word.erase(new_end, word.end());
            //加入词典
            Dic[word]++;
        }
    }
    //最后建立下标索引
    buildIndex(Dic);
}

string TextQuery::runQuery(const string &word)
{
    string res,tmp;
    // 从哈希表（缓存）中查找单词
    auto a = hash_word.find(word);
    if(a != hash_word.end()) {
        set<string> candidate;
        candidate = searchHashWord(word);
        for(auto index = candidate.begin(); index != candidate.end(); ++index) {
            tmp = *index;
            tmp += "\r\n";
            res += tmp;
        }
    }
    else
    {
        while(!candidate_.empty()) 
        {
            candidate_.pop();
        }
        for(auto c = word.begin(); c != word.end(); ++c) 
        {
            if(*c == 'a' || *c == 'o' || *c == 'u' || *c == 'e' || *c == 'i')
                continue;
            //在索引表中查找 编辑距离小于3的单词，
            auto get_map = (indexOfWords_.find(*c))->second;
            for(auto index = get_map.begin(); index != get_map.end(); ++index)
            {
                int res = editDistance(word.c_str(), (index->first).c_str());
                if(res < 3)
                {
                    candidate cand;
                    cand.word_ = index->first;
                    cand.distance_ = res;
                    cand.frequence_ = index->second;
                    candidate_.push(cand);
                }
            }
        }
        //输出符合条件的单词n个---  从优先级队列中
        for(int i = 0; i < 5; ++i) 
        {
            if(candidate_.empty()) 
            {
                break;
            }
            tmp = candidate_.top().word_;
            buildHashWord(word, tmp);//并把该单词放入
            tmp += "\r\n";
            res += tmp;
            candidate_.pop();
        }
    }

    return res;
}

//把单词放入哈希表
void TextQuery::buildHashWord(const string &word, const string &candidate) {
    hash_word[word].insert(candidate);
}

//从哈希表中查找
set<string> TextQuery::searchHashWord(const string &word) {
    auto a = hash_word.find(word);
    set<string> candidates;
    if(a != hash_word.end())
    {
        candidates = a->second;
    }
    return candidates;
}

//建立索引
void TextQuery::buildIndex(const map<string, int> &Dic_) {
   typedef map<string, int> maps;
   maps words[26];
   //从词典库查找，遍历每一个单词, 为每一个单词建立索引
   auto it = Dic_.begin();
   for(; it != Dic_.end(); ++it) {
        string s;
        s = it->first;//s为字典库中的单词
        auto c = s.begin();//c为单词的第一个字符指针
        char index_c = *c;//index_c为c的字符
        int index = index_c - 97;//a（97） - 97
        if(index >=0 && index <= 25) {
            words[index][s] = it->second;//存储单词及其相关信息
            indexOfWords_[index_c] = words[index];//建立索引,indexOfWords_[a] = words[0]
        }
   }
}


