#include <iostream>
#include <string>
#include <vector>
using namespace std;

//这里生成了一个临时的string对象
string shortString(const string &s1, const string &s2)
{
    return (s1.size() < s2.size()) ? s1 : s2;
}   
//这里在返回int时生成了一个临时的值
int get_val()
{
    int a = 2;
    return a;
}
int main(int argc, const char *argv[])
{
    cout << get_val() << endl;
    int res = get_val();
    cout << res << endl;
    return 0;
}
