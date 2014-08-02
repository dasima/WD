#include <iostream>
#include <map>
#include <stack>
#include <queue>
#include <typeinfo>
using namespace std;

int main(int argc, const char *argv[])
{
    map<string, int> word_count;
    cout << word_count.size() << endl;//0

    word_count["hello"];
    cout << word_count.size() << endl;//1
   
    word_count["hello"];
    cout << word_count.size() << endl;//1

    word_count["lo"];
    cout << word_count.size() << endl;//2
    return 0;
}
