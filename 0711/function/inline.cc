#include <iostream>
#include <string>
#include <vector>
using namespace std;
/*
 *這是一個宏函數，在預編譯期間調用處被替換成相應的代碼
 */
#define SWAP(a, b){\
int temp = *a;\
    *a = *b;\
    *b = temp;\
}
int main(int argc, const char *argv[])
{
    int a = 9;
    int b = 8;
    cout << "before a = " << a << " b = " << b << endl;
    SWAP(&a, &b);
    cout << "after a = " << a << " b = " << b << endl;
    return 0;
}
