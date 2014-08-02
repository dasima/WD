#include <iostream>
#include <string>
#include <list>
#include <algorithm>
using namespace std;
int main(int argc, const char *argv[])
{
    list<string> ls;
    ls.push_back("china");
    ls.push_back("america");
    ls.push_back("france");
    ls.push_back("canada");
    ls.push_back("russia");
    ls.push_back("england");

    list<string>::iterator res = find(ls.begin(), ls.end(), string("russia"));
    if(res == ls.end())
        cout << "not found" << endl;
    else
        cout << "found" << endl;
    ls.erase(res);
    cout << "......" << endl;
    for(list<string>::iterator it = ls.begin(); it != ls.end(); ++it){
        cout << *it << endl;    
    }
    ls.pop_front();
    cout << "......" << endl;
    for(list<string>::iterator it = ls.begin(); it != ls.end(); ++it){
        cout << *it << endl;    
    }

   ls.pop_back();
    cout << "......" << endl;
    for(list<string>::iterator it = ls.begin(); it != ls.end(); ++it){
        cout << *it << endl;    
    }

    ls.erase(ls.begin(), ls.end());
    cout << "......" << endl;
    for(list<string>::iterator it = ls.begin(); it != ls.end(); ++it){
        cout << *it << endl;    
    }

    return 0;
}
