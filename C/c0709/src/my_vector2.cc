#include <iostream>
#include <vector>
using namespace std;
int main()
{
    vector<int> col(9);//数组大小为9

    for(int i = 0; i != col.size(); ++i)
        col[i] = i + 1;//根据下标进行赋值

    //遍历打印
    cout << "打印数组元素:" << endl;
    for(int i = 0; i != col.size(); ++i)
        cout << col[i] << " ";
    cout << endl;
    return 0;
}
