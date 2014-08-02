#include <iostream>
#include <string>
#include <vector>
using namespace std;
/*
 *这里采用的是值传递，所以vec是一份副本，所有的改动均不影响原来的数组
 */
void push(vector<int> vec, int num)
{
    vec.push_back(num);
}
int main(int argc, const char *argv[])
{
    int num;
    vector<int> vec;
    while(cin >> num)
    {
        push(vec, num);
    }
    cout << "size = " << vec.size() << endl;
    for(int i: vec)
        cout << i << endl;
    return 0;
}
