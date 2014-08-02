#include "excep_stack.h"
#include <iostream>
using namespace std;

void foo()
{
    throw Exception("foobar");
}

void bar()
{
    foo();
}

int main(int argc, const char *argv[])
{
    try
    {
        bar();
    }catch(Exception &e)
    {
        cout << "reason:" << e.what() << endl;
        cout << "stack trace: " << e.stackTrace() << endl;
    }

    return 0;
}
