#include <iostream>
using namespace std;

template <typename T>
T abs(T val)
{
    return val > 0 ? val : -val;
}

int main(int argc, const char *argv[])
{
    double dval = 0.99;
    float fval = -9.9;

    cout << abs(-1) << endl;
    cout << abs(dval) << endl;
    cout << abs(fval) << endl;
    return 0;
}
