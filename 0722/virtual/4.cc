#include <iostream>
using namespace std;

class Test
{
    virtual void test();
    int a_;
};

int main(int argc, const char *argv[])
{
    cout << sizeof(Test) << endl;//8
    return 0;
}
