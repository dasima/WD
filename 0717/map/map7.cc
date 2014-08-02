#include <iostream>
#include <map>
#include<algorithm>
using namespace std;

int main(int argc, const char *argv[])
{
    map<string, int> m;
    m["beijing"] = 33;
    m["jinan"] = 38;
    m["xian"] = 31;
    m["wuhan"] = 37;

    map<string, int>::iterator it;
    string city;
    while(cin >> city)
    {
        it = m.find(city);
        if(it == m.end())
            cout << "failed" << endl;
        else
            cout << city << ":" << m[city] << endl;
    }
    return 0;
}
