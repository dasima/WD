#include <iostream>
using namespace std;

template <class T, size_t N>
void array_init(T (&arr)[N])
{
    for(size_t ix = 0; ix != N; ++ix)
        arr[ix] = ix;
}
