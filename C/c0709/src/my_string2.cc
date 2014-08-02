#include <iostream>
#include <string>
#include <vector>
using namespace std;
//字符串下标的使用
int main()
{
    string s = "running is good!";

    cout << "字符串string使用下标输出: " << endl;
    for(size_t ix = 0; ix != s.size(); ++ix)
        cout << s[ix] << " ";
    cout << endl;

    //字符串中的迭代器
    cout << "字符串使用迭代器顺序输出：" << endl;
    for(string::iterator iter = s.begin(); iter != s.end(); ++ iter)
        cout << *iter << " ";
    cout << endl;

    cout << "字符串使用迭代器逆序输出:" << endl;
    for(string::reverse_iterator iter = s.rbegin(); iter != s.rend(); ++iter)
        cout << *iter << " " ;
    cout << endl;
    return 0;
}
