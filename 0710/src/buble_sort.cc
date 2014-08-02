#include <iostream>
#include <string>
#include <vector>
#include <stdlib.h>

using namespace std;
void swap(vector<int> &ix, vector<int> &iy)
{
    vector<int> temp = ix;
    ix = iy;
    iy = temp;
}
void buble_sort(vector<int> &vec, bool(*cmp1)(int, int))
{
    vector<int>::size_type len = vec.size();
    for(vector<int>::size_type ix = 0; ix != len; ++ix)
    {
        for(vector<int>::size_type iy = 0; iy != len - ix - 1; ++iy)
        {
            if(vec[iy] > vec[iy + 1])
                swap(vec[iy], vec[iy + 1]);
        }
    }
}
bool cmp1(int a, int b)
{
    return a < b;
}
int main(int argc, const char *argv[])
{
    vector<int> vec;
    srand(1000);
    vec.push_back(rand() % 100);
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

    buble_sort(vec, cmp1);

    for(vector<int>::iterator it = vec.begin(); it != vec.end(); ++it)
    {
        cout << *it << endl;    
    }

    return 0;
}
