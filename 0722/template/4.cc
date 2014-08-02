#include <iostream>

using namespace std;

template <typename T, typename U>
void test(T a, U b)
{
   // T::size_type *p;
    typename T::size_type *p;
}

int main(int argc, const char *argv[])
{
    test(string("hello"), 6);
    return 0;
}
