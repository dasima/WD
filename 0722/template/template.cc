#include <iostream>

using namespace std;

template <typename T>
T add(const T &a, const T &b)
{
    return a + b;
}

template <typename T1, typename T2>
T1 add(const T1 &a, const T2 &b)
{
    return a + b;
}

template <typename T, size_t N>
void array_init(T(&param)[N])
{
    for(size_t ix = 0; ix != N; ++ix)
        param[ix] = 0;
}

typename<class Param, class U>
Param fcn(Param *array, U value)
{
    Param::size_type *p;
}


