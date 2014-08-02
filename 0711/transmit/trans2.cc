#include <iostream>
#include <string>
#include <vector>
using namespace std;
/*
 * 这里改为值引用，vec仅仅是main中vec的别名，
 * 对vec的任何操作都可以立刻反馈到main中的vec中
 */
void push(vector<int> &vec, int num)
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
