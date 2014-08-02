#include <iostream>
#include <string>
#include <vector>
using namespace std;
/*
 *num是int型，但我们输入字符串的时候，cin >> num是失败的。
 这种情况下会对num做一个初始化的操作
 */
int main(int argc, const char *argv[])
{
    int num = 9;
    cin >> num;

    cout << num << endl;
    cout << "-----------" << endl;
    return 0;
}
