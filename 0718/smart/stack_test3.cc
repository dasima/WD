#include <iostream>
#include "smart_ptr.h"
#include <stdexcept>
using namespace std;
int main(int argc, const char *argv[])
{
    try
    {
        //内存会释放
        Animal a;
        throw runtime_error("animal");
        
    }catch(runtime_error &e)
    {
        cout << e.what() << endl;
    }

    return 0;
}
