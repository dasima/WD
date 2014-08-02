#include <iostream>

using namespace std;

template <typename T1, typename T2>
T2 add(const T1 &a, const T2 &b)
{
    return a + b;
}
int main(int argc, const char *argv[])
{
    double a = add(2, 3.1);
    cout << a << endl;
    return 0;
}
