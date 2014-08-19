#include "text_corrector.h"
#include "string_utils.h"
#include <echo/exception.h>
#include <iostream>
#include <fstream>
#include <string>
#include <string.h>

using namespace std;
using namespace string_utils;

TextCorrector::TextCorrector(const string &filename)
{
    readFile(filename);    
}

TextCorrector::~TextCorrector()
{
}

void TextCorrector::readFile(const string &filename)
{
    ifstream in;
    in.open(filename.c_str());
    if(!in)
        throw Exception("open file failed!");
    string line;
    string word;
    while(getline(in, line))
    {
        for(string::iterator it = line.begin(); it != line.end(); ++it)
        {
            if(isspace(*it))
                break;
            //????
            //if(*it == '：')
              //  break;
            if(ispunct(*it))
                continue;
            if(isalpha(*it))
                continue;
            word = line;
            //cout << word << endl;
            break;
        }
        ++Dic_[word];
    }
}

string TextCorrector::textQuery(const string &word)
{
    string tmp = word;
    for(string::iterator it = tmp.begin(); it != tmp.end(); ++it)
    {
        for(map<string, int>::iterator mit = Dic_.begin(); mit != Dic_.end(); ++mit)
        {
            int dis = editDistance(tmp.c_str(), (mit->first).c_str());
            if(dis < 2)
            {
                cout << mit->first << endl;
            }
            return mit->first;
        }
    }
    return NULL; 
}
