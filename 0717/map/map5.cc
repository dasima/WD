#include <iostream>
#include <map>
#include <utility>
using namespace std;

void print(const map<string, int>::value_type &p)
{
    cout << p.first << "occurs: " << p.second << "times" << endl;
}
int main(int argc, const char *argv[])
{
    map<string, int> word_count;
    string word;
    std::pair<std::map<std::string, int>::iterator, bool> ret;
    while(cin >> word)
    {
        ret = word_count.insert(std::map<std::string, int>::value_type(word, 1));
       // ret = word_count.insert(make_pair(word, 1));
        if(!ret.second)
        {
            ++ret.first->second;
        }
    }

    for(map<string, int>::iterator iter = word_count.begin(); iter != word_count.end(); ++iter)
    {
        cout << iter->first << "  "  << iter->second << endl;
    }

    return 0;
}
