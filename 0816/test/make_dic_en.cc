#include "make_dic_en.h"
#include <echo/exception.h>
#include <fstream>
#include <stdlib.h>
#include <sstream>
#include <ostream>
#include <algorithm>
#include <functional>

using namespace std;

MakeDicEn::MakeDicEn(const string &filename)
{
    makeDicEn(filename);
}

void MakeDicEn::makeDicEn(const string &filename)
{
    ifstream in;
    in.open(filename.c_str());
    if(!in)
        throw Exception("open file failed!");
//        throw Exception("open file failed!");
    string line;
    while(getline(in, line))
        Lines_.push_back(line);
    in.close();

    ofstream out("dic_en.txt", ofstream::app);
    for(vector<string>::size_type ix = 0; ix != Lines_.size(); ++ix)
    {
        istringstream iss(Lines_[ix]);
        string word;
        while(iss >> word)
        {
            for(string::iterator it = word.begin(); it != word.end(); ++it)
            {
                if(isupper(*it))
                    tolower(*it);
                if(ispunct(*it))
                    *it = ' ';
            }
            string::iterator it = remove_if(word.begin(), word.end(), bind2nd(equal_to<char>(), ' '));
            word.erase(it, word.end());
            out << word << endl;
        }
    }
    out.close();
}


