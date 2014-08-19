#include "text_corrector.h"
#include "../include/string_utils.h"
#include <echo/exception.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <string.h>
#include <queue>

using namespace std;
using namespace string_utils;

TextCorrector::TextCorrector(const string &filename1, const string &filename2)
{
    readFileEn(filename1);    
    readFileCn(filename2);    
}

TextCorrector::~TextCorrector()
{
}

void TextCorrector::readFileEn(const string &filename)
{
    ifstream in;
    in.open(filename.c_str());
    if(!in)
        throw Exception("open file failed!");
    string line;
    string word;
    int frequence;
    while(getline(in, line))
    {
        istringstream iss(line);

        iss >> word >> frequence;
        Word new_word;
        new_word.Word_ = word;
        new_word.Distance_ = 5;
        new_word.Frequence_ = frequence;
        Dic_en_.insert(make_pair(word, new_word));
    }
    in.close();
}

void TextCorrector::readFileCn(const string &filename)
{
    ifstream in;
    in.open(filename.c_str());
    if(!in)
        throw Exception("open file failed!");
    string line;
    string word;
    int frequence;
    while(getline(in, line))
    {
        istringstream iss(line);
        iss >> word >> frequence;
        Word new_word;
        new_word.Word_ = word;
        new_word.Frequence_ = frequence;
        new_word.Distance_ = 5;
        Dic_cn_.insert(make_pair(word, new_word));
    }
    in.close();
}

string TextCorrector::textQuery(const string &word)
{
    cout << "c" << endl;
    string tmp = word;
    while(*(tmp.rbegin()) == '\r' || *(tmp.rbegin()) == '\n')
        tmp.resize(tmp.size() - 1);
    priority_queue<Word> queue;
    map<string, Word>::iterator mit;

    string res;
    int len = string_utils::getLenOfUTF8(tmp[0]);
    if(len >= 3)
    {
        mit = Dic_cn_.find(word);
        if(mit != Dic_cn_.end())
        {
            cout << word << endl;
            return word;
        }
        res = cnQuery(tmp);
    }
    else
    {
        //这里查询输出用两种方式
        //1. 查询到词典中有这个单词，就返回并输出
        //2. 词典中没有这个单词，则从词典中查询相近的几个单词，并输出
        //这里英文采用第二种
        //中文采用第一种
        //如果要输出多个，可以查询正确也输出几个相近的
        /*
        mit = Dic_en_.find(word);
        if(mit != Dic_en_.end())
        {
            cout << word << endl;
            return word;
        }
        */
        res = enQuery(tmp);
    }
    cout << res << endl;
    return res; 
}

string TextCorrector::cnQuery(const string &word)
{
    string tmp = word;
    priority_queue<Word> queue;
    map<string, Word>::iterator mit = Dic_cn_.begin();
    for(; mit != Dic_cn_.end(); ++mit)
    {
        int distance = string_utils::editDistance((mit->first).c_str(), word.c_str());
        if(distance < 3)
        {
            Word mword;
            mword.Distance_ = distance;
            mword.Word_ = mit->first;
            queue.push(mword);
        }
    }
    string res;
    string word_out;
    for(int i = 0; i < 3; ++i)
    {
        if(queue.empty())
            break;
        word_out = queue.top().Word_;
        //cout << word_out << endl;
        word_out += "\r\n";
        res += word_out;
        queue.pop();
    }
    return res;
}

//从英文词典中查询相近的单词---OK
string TextCorrector::enQuery(const string &word)
{
   // cout << "en" << endl;
    string tmp = word;
    priority_queue<Word> queue;
    map<string, Word>::iterator mit = Dic_en_.begin();
    for(; mit != Dic_en_.end(); ++mit)
    {
        int distance = string_utils::editDistance((mit->first).c_str(), word.c_str());
        if(distance < 2)
        {
            Word mword;
            mword.Distance_ = distance;
            mword.Word_ = mit->first;
            queue.push(mword);
        }
    }
    //cout << "dd" << endl;
    string res;
    string word_out;
    for(int i = 0; i < 3; ++i)
    {
        if(queue.empty())
            break;
        //cout << "res" << endl;
        word_out = queue.top().Word_;
        //cout << word_out << endl;
        word_out += "\r\n";
        res += word_out;
        queue.pop();
    }
    return res;
}


