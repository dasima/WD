#include <iostream>
#include <stack>
#include <map>
#include <queue>
#include <typeinfo>
using namespace std;

void print(const map<string, int>::value_type &p)
{
    cout << p.first << "occurs: " << p.second << "times" << endl;
}
int main(int argc, const char *argv[])
{
    map<string, int> word_count;
    string word;
    word_count["test"] = 10;
    word_count["foo"] = 5;
    word_count["bar"] = 12;

    cout << word_count.count("test") << endl;
    cout << word_count.count("hello") << endl;
    map<string, int>::iterator iter = word_count.find("test");
    if(iter == word_count.end())
        cout << "not found" << endl;
    else
        cout << iter->first << "  " << iter->second << endl;

    return 0;
}
