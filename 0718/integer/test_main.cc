#include "integer.h"
using namespace std;

int main(int argc, const char *argv[])
{
    Integer data(9);
    cout << data << endl;//9
    cout << ++data << endl;//10

    Integer data2(99);
    cout << data2 << endl;//99
    cout << data2++ << endl;//99
    return 0;
}
