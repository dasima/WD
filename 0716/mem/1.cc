#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <map>
#include <set>
#include <algorithm>
using namespace std;
int main(int argc, const char *argv[])
{
    //空数组
    vector<int> vec;
    cout << "size " << vec.size() << "  capacity " << vec.capacity() << endl;//0   0

    for(vector<int>::size_type ix = 0; ix != 24; ++ix)
        vec.push_back(ix);
    cout << "size " << vec.size() << "  capacity " << vec.capacity() << endl;//24  32
    //把最大可容纳空间设为50
    vec.reserve(50);
    cout << "size " << vec.size() << " capacity " << vec.capacity() << endl;//24  50
    //将现有空间填充
    while(vec.size() != vec.capacity())
        vec.push_back(9);
    cout << "size " << vec.size() << " capacity " << vec.capacity() << endl;//50  50
    //此时容器已满，在放入一个元素
    vec.push_back(9);
    cout << "size " << vec.size() << " capacity " << vec.capacity() << endl;//51   100
    

    return 0;
}
