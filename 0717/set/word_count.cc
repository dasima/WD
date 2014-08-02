#include <iostream>
#include <set>
#include <map>
#include <fstream>
using namespace std;
/*
void word_count(const set<string> &no_words, map<string, int> &word_count)
{
    string word;
    while(cin >> word)
    {
        if(!no_words.count(word))
        {
            ++word_count[word];
        }
    }
}
*/
int main(int argc, const char *argv[])
{
    set<string> no_words;
    no_words.insert("the");
    no_words.insert("is");
    no_words.insert("are");
    no_words.insert("am");

    map<string, int> word_count;
    string word;
    while(cin >> word)
    {
        if(!no_words.count(word))
        {
            ++word_count[word];
        }
    }
    for(map<string, int>::iterator it = word_count.begin(); it != word_count.end(); ++it)
    {
        cout << it->first << " occurs " << it->second << " times " << endl;
    }

    return 0;
}
