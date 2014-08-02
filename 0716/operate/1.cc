#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <algorithm>
using namespace std;
int main(int argc, const char *argv[])
{
    vector<string> vec;
    vec.push_back("china");
    vec.push_back("america");
    vec.push_back("england");

    vector<string>::iterator res = find(vec.begin(), vec.end(), string("china"));
    if(res == vec.end())
        cout << "not found " << endl;
    else
        cout << "found" << endl;

    //插入结果显示是在china前面插入了france
    //即insert 是在该迭代器上插入，该迭代器之前指向的元素后移
    vec.insert(res, "france");
    vec.insert(res, 3, "Russia");
    for(vector<string>::iterator it = vec.begin(); it != vec.end(); ++it){
        cout << *it << endl;    
    }

    //vector不支持push_front操作
   // vec.push_front("german");
    return 0;
}
