#include <iostream>
#include <string>
#include <vector>

using namespace std;
void swap(int *&a, int *&b)
{
    int temp(*a);
    *a = *b;
    *b = temp;
}
int main(int argc, const char *argv[])
{
    int i = 8;
    int j = 9;
    int *p = &i;
    int *q = &j;
    cout << i << " " << j << endl;
    swap(p, q); 
    cout << i << " " << j << endl;
    return 0;
}
