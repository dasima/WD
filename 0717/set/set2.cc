#include <iostream>
#include <set>
using namespace std;

int main(int argc, const char *argv[])
{
    set<string> s;
    s.insert("hello");
    s.insert("world");
    s.insert("how");
    s.insert("are");
    s.insert("you");

    for(set<string>::iterator it = s.begin(); it != s.end(); ++it)
    {
        cout << *it << endl;
    }

    cout << "---------------" << endl;
    s.erase("are");
    for(set<string>::iterator it = s.begin(); it != s.end(); ++it)
    {
        cout << *it << endl;
    }
    cout << "----------" << endl;

    set<string>::iterator it = s.find("you");
    if(it == s.end())
        cout << "404" << endl;
    else
        s.erase(it);
    for(set<string>::iterator it = s.begin(); it != s.end(); ++it)
    {
        cout << *it << endl;
    }

    return 0;
}
