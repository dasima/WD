#include <iostream>
#include <string>
#include <vector>

using namespace std;
int main(int argc, const char *argv[])
{
    //字符串的追加
    vector<string> vec;
    vec.push_back("baidu");
    vec.push_back("google");
    vec.push_back("yahoo");

    for(vector<string>::iterator it = vec.begin(); it != vec.end(); ++it){
        cout << *it << endl;    
    }

    //C++11提供的新式for循环，foreach
    //auto是C++11提供的自动类型推断
    for(const string &s:vec)
        cout << s << endl;
    
    for(const auto &s : vec)
        cout << s << endl;

    //自动推断迭代器类型
    for(auto it = vec.begin(); it != vec.end(); ++it){
        cout << *it << endl;    
    }
    return 0;
}
