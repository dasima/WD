#include <iostream>
using namespace std;
int main()
{
    //文本数据的读入和读取文本
    int in_number;
    cout << "Please input a number:";
    cin >> in_number;

    string in_name;
    cout << "Enter your name:";
    cin >> in_name;

    cout << in_name << " " << in_number << endl;
//求1到n的和
    int n = 5, sum = 0;
    for(int i = 0; i != n; ++i)
    {
        sum += i;
    }
    cout << "sum is :" << sum << endl;
//输入未知数目的元素
    sum = 0;
    int value;
    while(cin >> value)
    {
        sum += value;
    }
    cout << "Sum is :" << sum << endl;
    return 0;
}
