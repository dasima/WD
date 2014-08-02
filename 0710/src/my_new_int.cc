#include <iostream>
#include <string>
#include <vector>

using namespace std;
int main(int argc, const char *argv[])
{
    int *ptr = new int;
    cout << *ptr << endl;

    int *ptr2 = new int(12);
    cout << *ptr2 << endl;

    int *ptr3 = new int[9];

    int **ptr4 = new int*[9];
    for(int i = 0; i != 9; ++i)
    {
        ptr4[i] = new int[7];
    }

    for(int i = 0; i != 9; ++i)
    {
        delete[] ptr4[i];
    }
    delete[] ptr4;
    delete ptr;
    delete ptr2;
    delete[] ptr3;
    return 0;
}
