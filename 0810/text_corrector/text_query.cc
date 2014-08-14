#include "text_query.h"
#include <echo/exception.h>
#include <stdio.h>
#include <fstream>
#include <sstream>
#include <iostream>
using namespace std;

TextQuery::TextQuery(const string &filename)
{
    readFile(filename);
}

//读取文件，并建立单词到关联行号的map容器的映射
void TextQuery::readFile(const string &filename)
{
    //1. 打开文件
    ifstream in;
    in.open(filename.c_str());
    if(!in)
        throw Exception("open file failed!");

    //2. 存储输入文件
    //读取每一行到line中，并存储到vector对象lines_中
    string line;
    while(getline(in, line))
        lines_.push_back(line);
    in.close();

    /*
     *过滤没实现
     */
    set<string> exclude_words;
    exclude_words.insert("a");
    exclude_words.insert(".");
    exclude_words.insert(",");
    exclude_words.insert("?");
    exclude_words.insert("!");
    exclude_words.insert(":");
    exclude_words.insert(";");
    exclude_words.insert("\"");

    //3. 建立从单词关联到行号的map容器
    for(vector<string>::size_type line_num = 0; line_num != lines_.size(); ++line_num)
    {
        //将每一行分解为单词，对每一个单词进行操作
        istringstream iss(lines_[line_num]);
        string word;
        while(iss >> word)
        {
            //大写换小写
            for(string::iterator it = word.begin(); it != word.end(); ++it)
            {
                if(isupper(*it))
                    tolower(*it);
                if(ispunct(*it))
                    *it = ' ';
            }
            ++dic_[word];
        }
    }
}

//查询功能
string TextQuery::runQuery(const string &word) const
{
    map<string, int>::const_iterator loc;//const_iterator???
    loc = wordMap_.find(word);
    //如果有这个单词，则输出该单词
    //否则，单词插入词库，并执行相关单词匹配
    if(loc != wordMap_.end())
        cout << word << endl;
    else
    {
        wordMap_.insert(word);
        //wordCompare(word);
      //  printResult();
    }
    return NULL;
}   

//打印输出
/*
string TextQuery::printResult(const string &word, const set<LineNo> &result) const
{
    string ret;
    size_t size = result.size();
    char buf[32];
    snprintf(buf, sizeof(buf), "%u", size);
    ret = word + " occurs " + buf + " time(s)\n";
    
    for(set<LineNo>::iterator it = result.begin(); it != result.end(); ++it)
    {
        snprintf(buf, sizeof(buf), "%u", *it + 1);
        ret += string("line") + buf + ")";
        ret += lines_[*it] + "\n";
    }
    return ret;
}
*/

/*
int TextQuery::shortestLength(const string &A,
                   const string &B,
                   int i,
                   int j)
{
    if(i == 0 || j == 0)
        return 0;
    if(emon[i][j] != -1)
        return emon[i][j];
    if(A[i-1] = B[j-1])
    {
        emon[i][j] = shortestLength(A, B, i-1, j-1);
        return emon[i][j];
    }
    else
    {
        int t1 = shortestLength(A, B, i-1, j);
        int t2 = shortestLength(A, B, i-1, j-1);
        int t3 = shortestLength(A, B, i, j-1);
        int min ;
        min = t1 < t2 ? t1 : t2;
        emon[i][j] = min < t3 ? min : t3;
        return emon[i][j];
    }
}
*/


//将符合条件的单词放入words_中

/*
string TextQuery::wordCompare(const string &word)
{
    for(map<string, int>::iterator it = wordMap_.begin(); it != wordMap_.end(); ++it)
    {
        string s = *it;
        if(shortestLength(s, word, sizeof(s), sizeof(word)) < 3)
        {
            words_.push_back(s);
        }
    }
}
*/













