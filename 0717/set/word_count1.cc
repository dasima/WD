#include <iostream>
#include <string.h>
#include <string>
#include <map>
#include <set>
#include <fstream>
#include <algorithm>
#include <stdexcept>
using namespace std;
ifstream &open_file(ifstream &in, const string &filename)
{
    in.close();
    in.clear();
    in.open(filename.c_str());
    return in;
}

void restricted_wc(ifstream &input_file, const set<string> &exclude_words, map<string, int> &word_count)
{
    string word;
    while(input_file >> word)
    {
        if(!exclude_words.count(word))
            ++word_count[word];
    }
    input_file.close();
    input_file.clear();
}

void print(const string &s)
{
    cout << s << " " ;
}

void print_map(const map<string, int>::value_type &m)
{
    cout << m.first << " occurs " << m.second << " times " << endl;
}


int main(int argc, const char *argv[])
{
    map<string, int> word_count;
    set<string> exclude_words;
    exclude_words.insert("the");
    exclude_words.insert("a");
    exclude_words.insert("an");
    exclude_words.insert("is");
    exclude_words.insert("and");

    ifstream infile;
    string name = "in.txt";
    if(!open_file(infile, name))
    {
        throw std::runtime_error("open file error!");
    }
    restricted_wc(infile, exclude_words, word_count);

    
    for(map<string, int>::iterator it = word_count.begin(); it != word_count.end(); ++it)
    {
        cout <<  it->first << "    " << it->second << endl;
    }
    return 0;
}
