#include <iostream>
#include <string>
#include <vector>
using namespace std;
int main(int argc, const char *argv[])
{
    int num = 9;
    cin >> num;

    cout << num << endl;
    cout << "bad = " << cin.bad() << endl;
    cout << "eof = " << cin.eof() << endl;
    cout << "fail = " << cin.fail() << endl;

    /*
     *上面输入非法数据，cin内部某些状态发生改变
     *cin就是不可用的
     */
    string s = "hello";
    cin >> s;
    cout << "string = " << s << endl;
    cout << "bad = " << cin.bad() << endl;
    cout << "eof = " << cin.eof() << endl;
    cout << "fail = " << cin.fail() << endl;
    cout << "good = " << cin.good() << endl;

    cout << "-----------" << endl;
    return 0;
}
