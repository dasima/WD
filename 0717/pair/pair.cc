#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <map>
#include <set>
#include <algorithm>
#include <utility>
using namespace std;
int main(int argc, const char *argv[])
{
    //不指定初始值
    std::pair<int, string> p1;
    p1.first = 1;
    p1.second = "test";
    cout << p1.first << "  " << p1.second <<endl; 

    //可直接指定初始值
    std::pair<int, int>p2(4, 5);
    cout << p2.first << "  " << p2.second << endl;

    std::pair<string, string>p3("hello", "world");
    cout << p3.first << "  " << p3.second << endl;

    make_pair(1, 2);

    make_pair(string("hello"),1);
    vector<string> v1;
    vector<list<string> > v2;
    make_pair(v1, v2);
    return 0;
}
