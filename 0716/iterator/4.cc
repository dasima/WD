#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <algorithm>
using namespace std;
int main(int argc, const char *argv[])
{
    list<string> ls;
    ls.push_back("nanshan");
    ls.push_back("luohu");
    ls.push_back("futian");

    for(list<string>::iterator it = ls.begin(); it != ls.end(); ++it){
        cout << *it << endl;    
    }

    cout << "---------------" << endl;
    for(list<string>::reverse_iterator it = ls.rbegin(); it != ls.rend(); ++it){
        cout << *it << endl;    
    }
    return 0;
}
