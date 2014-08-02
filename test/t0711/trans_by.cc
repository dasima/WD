#include <iostream>
#include <string>
#include <vector>
using namespace std;

void TransByValue(int x);
void TransByReference(int &x);
void TransByAddress(int *x);
int main(int argc, const char *argv[])
{
    int a = 0;
    TransByValue(a);
    cout << "transmit by value: " << a << endl;//0

    a = 0;
    TransByReference(a);
    cout << "transmit by reference: " << a << endl;//9
    
    a = 0;
    TransByAddress(&a);
    cout << "transmit by address: " << a << endl;//1
    return 0;
}
void TransByValue(int x)
{
    x += 10;
}
void TransByReference(int &x)
{
    x += 9;
}
void TransByAddress(int *x)
{
    *x = (*x + 1);
}
