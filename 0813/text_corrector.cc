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
#include <functional>

using namespace std;

TextCorrector::TextCorrector(const string &filename)
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
            //移除空格
            string::iterator it = remove_if(word.begin(), word.end(), bind2nd(equal_to<char>(), ' '));
            word.erase(it, word.end());
            ++Dic_[word];
        }
    }
    /*
     *下面在建立索引前输出word，查看是否word处理正确
     */
   // auto icc = Dic_.begin();
   // for(; icc != Dic_.end(); icc++) {
   //     cout << icc -> first << endl;
   // }
    //为词库建立索引
    buildIndex();
    /*
     *下面把索引输出了一遍
    map<char, map<string, int> >::iterator it;
    map<string ,int>::iterator itt;
    for(it = index_.begin(); it != index_.end(); ++it)
    {
        cout << it->first << endl;
        for(itt = it->second.begin(); itt != it->second.end(); ++itt)
        {
            cout << itt->first << endl;
        }
    }
    */
}


string TextCorrector::textQuery(const string &word)
{
    //1.先进行单词转换,取出客户端发送时词尾的/r/n
    string tmp = word;
    string res;
    string tmp2;
    while(*tmp.rbegin() == '\r' || *tmp.rbegin() == '\n')
    {
        tmp.resize(tmp.size() -1);
    }
    //2.先从缓存中查找
    auto a = cache_.find(tmp);
    //查找成功
    if(a != cache_.end())
    {
        set<string> candidate;
        candidate = searchFromCache(word);
        //auto --- set<string>::iterator
        for(auto index = candidate.begin(); index != candidate.end(); ++index)
        {
            tmp2 = *index;
            tmp2 += "\r\n";
            res += tmp2;
        }
    }

    //3.缓存中没找到就从词典中查找单词
    //auto --- string::iterator
    else
    {
        //先把队列清空
        while(!queue_.empty())
        {
            queue_.pop();
        }
        for(auto c = tmp.begin(); c != tmp.end(); ++c)
        {
            //对词典中可能出现的比较多的单词过滤掉
            if(*c == 's' )
                continue;
            //非字符，过滤掉
            if(!isalpha(*c))
                continue;
            //一个字符只从索引中搜索一次
            /*
            for(auto a = tmp.begin(); a != tmp.end(); ++a)
            {
                for(auto b = tmp.begin(); b != a; ++b)
                {
                    if(*a == *b)
                    {
                        tmp.erase(b);
                        --a;
                        --b;
                    }
                }
            }
            */
            //auto --- map<string, int>
            //根据索引找到索引所匹配的字符串集合
            auto get_index = index_.find(*c)->second;
            //auto --- set<string>::iterator
            //对集合中的每一个单词
            for(auto index = get_index.begin(); index != get_index.end(); ++index)
            {
                //计算编辑距离
                int dis = editDistance(tmp.c_str(), (index->first).c_str());
                //这里控制编辑距离为2
                if(dis < 2)
                {
                    Word candidate;
                    candidate.word_ = index->first;
                    candidate.distance_ = dis;
                    candidate.frequence_ = index->second;
                    //把符合条件的单词添加进优先队列

                     // 下面是为了防止出现队列中重复的单词
                    priority_queue<Word> queue = queue_;
                    while(!queue.empty())
                    {
                        if(queue.top().word_ == candidate.word_)
                            break;
                        queue.pop();
                    }
                    if(queue.empty())
                        queue_.push(candidate);
                    //set_cache.insert(candidate);
                }
            }
            /*
            set<Word>::iterator set_it;
            for(set_it = set_cache.begin(); set_it != set_cache.end(); ++set_it)
            {
                queue_.push(*set_it);
            }
            */
        }
        //这里控制输出的单词数
        string word_out;
        int i;
        for(i = 0; i < 3; ++i)
        {
            if(queue_.empty())
            {
                break;
            }
            word_out = queue_.top().word_;
            buildCache(word, word_out);
            cout << word_out << endl;//这里在服务器端输出查询到的单词
            word_out += "\r\n";
            res += word_out;
            queue_.pop();
        }
    }
    return res;
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

//建立huancun
void TextCorrector::buildCache(const string &word, const string &word_cache)
{
    cache_[word].insert(word_cache);
}

set<string> TextCorrector::searchFromCache(const string &word)
{
    auto a = cache_.find(word);
    //候选集
    set<string> candidates;
    if(a != cache_.end())
    {
        candidates = a->second;
    }
    return candidates;
}

//从词典中查找
/*
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
   */

//建立索引
void TextCorrector::buildIndex()
{
    map<string, int>::iterator it;
    map<string, int> words[26];

    for(it = Dic_.begin(); it != Dic_.end(); ++it)
    {
        string word = it->first;
        char index_c = *(word.begin());
        int index =(index_c) - 97;
        if(index >= 0 && index <= 25)
        {
            words[index][word] = it->second;//??
            index_[index_c] = words[index];
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
