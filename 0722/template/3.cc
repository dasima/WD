#include <iostream>

using namespace std;

template <typename T, size_t N>
void print(T (&arr)[N])
{
    for(size_t ix = 0; ix != N; ++ix)
        cout << arr[ix] << " " ;
    cout << endl;
}

int main(int argc, const char *argv[])
{
    int arr[5] = {1, 3, 4, 6, 2};
    print(arr);
    
    return 0;
}
