#include <iostream>
using namespace std;
int main()
{
    //打印数据类型的大小
    cout << "bool :" << sizeof(bool) << endl;
    cout << "int :" << sizeof(int) << endl;
    cout << "char :" << sizeof(char) << endl;
    cout << "double :" << sizeof(double) << endl;
    cout << "float " << sizeof(float) << endl;
    cout << "long :" << sizeof(long) << endl;
   //引用
    int a = 9;
    cout << "a = " << a << endl;
    cout << "a is at address:" << &a << endl;

    int &ref = a;
    cout << "ref is at address:" << &ref << endl;

    int &ref2 = ref;
    cout << "ref2 is at address:" << &ref2 << endl;
    cout << "ref2 gets value " << ref2 << endl;
    //引用
    string s = "test";
    string &s_ref = s;
    cout << "s_ref gets value:" << s_ref << endl;
    return 0;
}
