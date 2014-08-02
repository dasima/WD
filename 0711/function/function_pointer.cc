#include <iostream>
#include <stdlib.h>
#include <string>
#include <vector>
using namespace std;
inline void swap(int &a, int &b)
{
    int temp(a);
    a = b;
    b = temp;
}
bool cmp(int a, int b)
{
    return a > b;
}
void buble_sort(vector<int> &vec, bool(*cmp)(int, int))
{
    typedef vector<int>::size_type pos;
    for(pos ix = 0; ix < vec.size() - 1; ++ix)
    {
        for(pos iy = 0; iy < vec.size() - ix - 1; ++ iy)
        {
            if(cmp(vec[iy], vec[iy + 1]))
            {
                swap(vec[iy], vec[iy + 1]);
            }
        }
    }
}

int main(int argc, const char *argv[])
{
    vector<int> vec;
    srand(time(NULL));//以系统时间作为种子，每次生成的数据是随机的
   // srand(1);//
   // srand(1000);//srand中种子是常数，每次运行生成的数据都是一样的
    vec.push_back(rand() % 100);
    vec.push_back(rand() % 100);
    vec.push_back(rand() % 100);
    vec.push_back(rand() % 100);
    vec.push_back(rand() % 100);
    vec.push_back(rand() % 100);
    vec.push_back(rand() % 100);

    for(vector<int>::iterator it = vec.begin(); it != vec.end(); ++it)
    {
        cout << *it << endl;    
    }
    cout << endl;

    buble_sort(vec, cmp);
    for(vector<int>::iterator it = vec.begin(); it != vec.end(); ++it)
    {
        cout << *it << endl;    
    }
    cout << endl;
    return 0;
}
