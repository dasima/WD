#include <iostream>

using namespace std;

template <typename T>
T add(const T &a, const T &b)
{
    return a + b;
}
int main(int argc, const char *argv[])
{
    int a = add(2, 3);
    cout << a << endl;
    return 0;
}
