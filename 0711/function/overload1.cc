#include <iostream>
#include <string>
#include <vector>
using namespace std;
string sum(const string &a, const string &b)
{
    return a + b;
}
int sum(int a, int b)
{
    return a + b;
}
int main(int argc, const char *argv[])
{
    string s1 = "hello";
    string s2 = "world";
    cout << sum(s1, s2) << endl;

    int a = 1;
    int b = 2;
    cout << sum(a, b) << endl;
    return 0;
}
