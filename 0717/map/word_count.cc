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

    while(cin >> word)
        ++word_count[word];

    for(map<string, int>::iterator iter = word_count.begin(); iter !=  word_count.end(); ++iter)
    {
        cout << iter->first << "  " << iter->second << endl;
    }

    return 0;
}
