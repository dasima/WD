#include "exception.h"
#include <iostream>
using namespace std;

void foo()
{
    cout << "exception..." << endl;
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
        cout << e.what() << endl;
    }
    return 0;
}
