#include <iostream>
#include <string>
#include <vector>
using namespace std;
/*
 *宏定义函数，不进行调用，编译器就无法检查它的错误
 */
#define TEST\
    {\
        hello\
    }
inline void test1()
{
   // hello;
    cout << "world" << endl;
}
int main(int argc, const char *argv[])
{
    //TEST;
    return 0;
}
