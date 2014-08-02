#include <iostream>
#include <vector>
using namespace std;
int main()
{
    vector<int> col(9);//数组大小为9

    for(int i = 0; i != col.size(); ++i)
        col[i] = i + 1;//赋值

    cout << "顺序输出";
    for(vector<int>::iterator iter = col.begin(); iter != col.end(); ++iter)
        cout << *iter << " ";
    cout << endl;

    cout << " 逆序输出数组元素：" ;
    for(vector<int>::reverse_iterator iter = col.rbegin(); iter != col.rend(); ++iter)
        cout << *iter << " ";
    cout << endl;
    return 0;
}
