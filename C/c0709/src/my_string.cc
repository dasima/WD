#include <iostream>
#include <vector>
#include <string>
using namespace std;
int main()
{
    string s1 = "kobe";
    string s2("bryant");
    string s3;//空字符串

    cout << s1 << endl;
    cout << "字符串s1的长度" << s1.size() << endl;//求长度

    s3 = s1;//字符串间的复制
    s3 += " ";
    s3 += s2;//字符串的拼接
    cout << s3 << endl;

    //比较大小
    cout << "比较大小";
    cout << "s1 小于 s2？ "<< (s1 < s2) <<endl;
    cout << "s1 等于s3 ?" << (s1 == s3) << endl;
    return 0;
}
