#include <iostream>
#include <string>
#include <vector>
using namespace std;
/*
 *这里是内联函数，代码在编译期间进行扩展
 */
inline void swap(int* a, int* b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}
int main(int argc, const char *argv[])
{
    int a = 9;
    int b = 8;
    cout << "before a = " << a << " b = " << b << endl;
    swap(&a, &b);
    cout << "after a = " << a << " b = " << b << endl;
    return 0;
}
