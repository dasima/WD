#include <iostream>
#include <vector>
using namespace std;
int main()
{
    vector<int> col;//声明一个空数组
    for(int i = 1; i != 6; ++i)
        col.push_back(i);//往数组追加元素

    //遍历打印
    for(int i = 0; i != col.size(); ++i)
        cout << col[i] << " ";
    cout << endl;
    return 0;
}
