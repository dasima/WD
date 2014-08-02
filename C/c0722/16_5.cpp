#include <iostream>
using namespace std;

template <typename T>
T &bigger(const T& t1, const T& t2)
{
    return t1 > t2 ? t1 : t2;
}
//NO
int main(int argc, const char *argv[])
{
    string s1 = "hi";
    string s2 = "world";
    string s = bigger(s1, s2);
    cout << s << endl;
    return 0;
}
