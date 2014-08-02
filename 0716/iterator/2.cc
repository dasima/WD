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
    vec.push_back("meituan");
    vec.push_back("baidutuan");
    vec.push_back("lashou");
    vec.push_back("wowo");
    
    vector<string>::iterator res = find(vec.begin(), vec.end(), string("lashou"));
    if(res == vec.end())
        cout << "not found " << endl;
    else
        cout << "found" << endl;

    //用一段区间去初始化另一个新容器
   // vector<string> vec2(vec.begin(), res);
    vector<string> vec2(res, vec.end());
    for(vector<string>::iterator it = vec2.begin(); it != vec2.end(); ++it){
        cout << *it << endl;    
    }

    //用一段迭代器范围去初始化另一种容器
    list<string> ls(vec.begin(), vec.end());
    for(auto &item: ls)
    {
        cout << item << endl;        
    }

    //wrong，不能用vector初始化list
  /*  list<string> ls2(vec);
    for(auto &item: ls2)
    {
            cout << item << endl;
    }
    */

    list<string> lst;
    lst.push_back("nba");
    lst.push_back("cba:");
   // cout << lst[0] << endl;//?????
    return 0;
}
