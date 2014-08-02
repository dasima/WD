#include "excep_stack.h"
#include <iostream>
using namespace std;

class Bar
{
    public:
       void test()
       {
        throw Exception("opps");
       }
};

void foo()
{
    Bar bar;
    bar.test();
}
int main(int argc, const char *argv[])
{
    try
    {
        foo();
    }catch(const Exception &e)
    {
        cout << "reason --- " << e.what() << endl;
        cout << "stack trace--- " << e.stackTrace() << endl;
    }
    
    return 0;
}
