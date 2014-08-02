#include <iostream>
#include <map>
using namespace std;

void print(const map<string, int>::value_type &p)
{
    cout << p.first << "occurs: " << p.second << "times" << endl;
}
int main(int argc, const char *argv[])
{
    map<string, int> word_count;
    string word;

    word_count.insert(map<string, int>::value_type("hello", 1));
    for(map<string, int>::iterator iter = word_count.begin(); iter !=  word_count.end(); ++iter)
    {
        cout << iter->first << "  " << iter->second << endl;
    }
    cout << "-------------" << endl;

    word_count.insert(make_pair("test", 3));
    for(map<string, int>::iterator iter = word_count.begin(); iter !=  word_count.end(); ++iter)
    {
        cout << iter->first << "  " << iter->second << endl;
    }
    cout << "-------------" << endl;
    
    pair<map<string, int>::iterator, bool> ret = word_count.insert(map<string, int>::value_type("hello", 4));
    for(map<string, int>::iterator iter = word_count.begin(); iter !=  word_count.end(); ++iter)
    {
        cout << iter->first << "  " << iter->second << endl;
    }
    cout << "-------------" << endl;

    cout << ret.first->first << endl;
    cout << ret.first->second << endl;
    cout << ret.second << endl;

    return 0;
}
