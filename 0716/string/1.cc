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
    string s = "helloworld";
    s.insert(2, 5, 'a');//在s的s[2]位置插入5个字符'a'
    cout << s << endl;

    s.insert(4, "test");//在s[4]位置插入字符串"test"
    cout << s << endl;

    s.insert(2, "test", 3);//在s[2]位置插入test的长度为3的字符（即tes）
    cout << s << endl;

    s = "helloworld";
    string str = "foobar";
    s.insert(5, str, 3, 2);//在s[5]插入str[3]开始的2个字符
    cout << s << endl;

    s = "helloworld";
    string str2 = "foobar";
    s.insert(0, str2);//在s[0]位置插入字符串str2
    cout << s << endl;

    string s2 = "helloworld";
    s2.erase(4, 5);//擦除s2[4]位置开始的5个字符
    cout << s2 << endl;

    s = "helloworld";
    cout << s.substr(5, 3) << endl;//s[5]开始的3个字符
    s.append("hello");
    cout << s << endl;
    return 0;
}
