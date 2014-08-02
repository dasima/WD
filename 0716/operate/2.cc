#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <map>
#include <set>
#include <algorithm>
using namespace std;
int main(int argc, const char *argv[])
{
    vector<string> vec;
    vec.push_back("shenzhen");
    vec.push_back("beijing");

    list<string> ls(vec.begin(), vec.end());
    ls.push_front("guangzhou");
    for(auto &item: vec){
        cout << item << endl;        
    }
    return 0;
}
