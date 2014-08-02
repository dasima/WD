#include <iostream>
#include <string>
using namespace std;
int main()
{
    string s = "Tracy McGrady";
    cout << "string 可以转化为c风格的字符串" << endl;
    cout << "字符串s：" << s.c_str() << endl;
    cout << endl;

    cout << "在string 中查找字符" << endl;
    cout << "查找字符t :" ;
    string::size_type pos = s.find("t");
    if(pos != string::npos)
    {
        cout << pos << endl;
        cout << s[pos] << endl;
    }
    else
        cout << "not found" << endl;

    cout << "查找字符T : " ;
    pos = s.find("T");
    if(pos != string::npos)
    {
        cout << pos << endl;
        cout << s[pos] << endl;
    }
    else
        cout << "not found" << endl;

    s = "shenzhen";
    cout << s << endl;

    cout << "使用getline读入字符串" << endl;
    cout << "输入字符串:" << endl;
    getline(cin, s);
    cout << s << endl;
    return 0;
}

