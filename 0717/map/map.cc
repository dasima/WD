#include <stack>
#include <iostream>
#include <map>
#include <queue>
#include <typeinfo>
using namespace std;

void print(const pair<string, int> &p)
{
    cout << p.first << "  " << p.second << endl;
}

int main(int argc, const char *argv[])
{
    map<string, int> people;
    people["beijing"] = 1000;
    people["shanghai"] = 2000;
    people["shenzhen"] = 3000;

    cout << people.size() << endl;

    cout << people["beiijing"] << endl;
    cout << people["beijing"] << endl;

    people["beijing"] = 8000;
    map<string, int>::iterator iter = people.begin();
    cout << people.size() << endl;
    while(iter != people.end())
    {
        cout << iter-> first << "  " << iter->second << endl;
        ++iter;
    }

    cout << "--------" << endl;

   // foreach(people.begin(), people.end(), print);
    
    return 0;
}
