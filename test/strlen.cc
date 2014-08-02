#include <iostream>
#include <string.h>
#include <vector>

using namespace std;

int main(int argc, const char *argv[])
{
    char a[] = "abcde";
    cout << sizeof(a) << endl;//6
    cout << strlen(a) << endl;//5

    char b[10] = "abcde";
    cout << sizeof(b) << endl;//10
    cout << strlen(b) << endl;//5

    int c[10] = {0};
    cout << sizeof(c) << endl;//40
    return 0;
}
