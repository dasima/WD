#include <iostream>
#include <string>

using namespace std;

void test(int i, double d)
{
    cout << i << " " << d << endl;
}

int main(int argc, const char *argv[])
{
    void(*pfunc)(int, double) = &test;
    pfunc(1, 2.34);
    return 0;
}
