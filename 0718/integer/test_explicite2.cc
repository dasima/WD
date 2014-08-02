#include "integer.h"

void print(const Integer &t)
{
    cout << t << endl;
}
int main(int argc, const char *argv[])
{
    Integer t(9);
    print(t);
    print(99);
    return 0;
}
