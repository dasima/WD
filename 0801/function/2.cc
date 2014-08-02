#include <iostream>
#include <string>
#include <functional>

using namespace std;

//c++11新标准
void test(int i, double d)
{
    cout << i << " " << d << endl;
}

int main(int argc, const char *argv[])
{
    //void(*)(int, double)
    function<void(int, double)> fp;
    fp = test;
    fp(1, 2.34);

    return 0;
}
