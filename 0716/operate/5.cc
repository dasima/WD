#include <iostream>
#include <string>
#include <list>
#include <list>
#include <map>
#include <set>
#include <algorithm>
using namespace std;
int main(int argc, const char *argv[])
{
    list<string> ls;
    ls.push_back("bj");
    ls.push_back("sh");
    ls.push_back("gz");
    for(list<string>::iterator it = ls.begin(); it != ls.end(); ++it){
        cout << *it << endl;    
    }

   // ls.pop_back();
    ls.pop_front();
    for(list<string>::iterator it = ls.begin(); it != ls.end(); ++it){
        cout << *it << endl;    
    }
    return 0;
}
