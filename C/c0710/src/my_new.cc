#include <iostream>
#include <string>
#include <vector>
using namespace std;

int main(int argc, const char *argv[])
{
    //new 动态二维数组的申请
    int **p = new int* [5];
    for(int i = 0; i != 5; ++i)
        p[i] = new int[4];

    //delete 动态二维数组的释放
    for(int i = 0; i != 5; ++i)
        delete[] p[i];
    delete[] p;
    return 0;
}
